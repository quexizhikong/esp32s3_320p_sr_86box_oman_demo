#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdatomic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "i2c_device.h"
#include "touch_data.h"

typedef struct _rtch_info_t {
    atomic_short x;
    atomic_short y;
    atomic_bool touched;
} touch_info_t;

static I2CDevice_t gslx6870_device;
static touch_info_t touch_info;

static void IRAM_ATTR touch_isr_handler(void* arg) {
    TaskHandle_t task_handle = (TaskHandle_t)arg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(task_handle, 0, eNoAction, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
}

static void touch_gsl6870_load_fw(void) {
    uint8_t buf[32] = {0};
    uint8_t reg = 0;

    unsigned int source_line = 0;
    unsigned int source_len = sizeof(GSLX680_FW) / sizeof(GSLX680_FW[0]);

    for (source_line = 0; source_line < source_len; source_line++) {
        reg = GSLX680_FW[source_line].offset;

        buf[0] = (char)(GSLX680_FW[source_line].val & 0x000000ff);
        buf[1] = (char)((GSLX680_FW[source_line].val & 0x0000ff00) >> 8);
        buf[2] = (char)((GSLX680_FW[source_line].val & 0x00ff0000) >> 16);
        buf[3] = (char)((GSLX680_FW[source_line].val & 0xff000000) >> 24);

        i2c_write_bytes(gslx6870_device, reg, buf, 4);
    }
}

static void gslx6870_deal(uint8_t* touch_data, int16_t* x, int16_t* y, uint8_t* touched) {
    static struct gsln_touch_info cinfo = {0};
    cinfo.x[0] = (touch_data[7] & 0x0f) << 8 | touch_data[6];
    cinfo.y[0] = (touch_data[5] << 8) | touch_data[4];
    cinfo.id[0] = ((touch_data[7] & 0xf0) >> 4);
    cinfo.finger_num = (touch_data[3] << 24) | (touch_data[2] << 16) | (touch_data[1] << 8) | touch_data[0];
    gsln_alg_id_main(&cinfo);
    int mask = gsln_mask_tiaoping();
    if (mask > 0 && mask < 0xffffffff) {
        touch_data[0] = 0xa;
        touch_data[1] = 0;
        touch_data[2] = 0;
        touch_data[3] = 0;
        i2c_write_bytes(gslx6870_device, 0xf0, touch_data, 4);
        touch_data[0] = (uint8_t)(mask & 0xff);
        touch_data[1] = (uint8_t)((mask >> 8) & 0xff);
        touch_data[2] = (uint8_t)((mask >> 16) & 0xff);
        touch_data[3] = (uint8_t)((mask >> 24) & 0xff);
        i2c_write_bytes(gslx6870_device, 0x08, touch_data, 4);
    }
    *x = cinfo.x[0];
    *y = cinfo.y[0];
    *touched = cinfo.finger_num > 0;
}

static void gslx6870_read_task(void* arg) {
    uint32_t skip_intr = (uint32_t)arg;
    printf("skip_intr:%d\r\n",skip_intr);

    touch_gsl6870_load_fw();
    i2c_write_byte(gslx6870_device, 0xe4, 0x04);
    i2c_write_byte(gslx6870_device, 0xe0, 0x00);
    vTaskDelay(pdMS_TO_TICKS(2));
    gsln_DataInit(gsln_config_data_id);

    vTaskPrioritySet(NULL, 5);

    uint8_t touch_data[8];
    int16_t x = 0, y = 0;
    int16_t x_last = 0, y_last = 0;
    uint8_t touched;
    
    for (;;) {
        if (skip_intr == 0) {
            xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
        }
       // printf("touch_isr_handler\r\n");

        i2c_read_bytes(gslx6870_device, 0x80, touch_data, 8);
        gslx6870_deal(touch_data, &x, &y, &touched);

        while (touched) {
            atomic_store(&touch_info.x, x);
            atomic_store(&touch_info.y, y);
            atomic_store(&touch_info.touched, true);

            if (x_last == x && y_last == y) {
                vTaskDelay(pdMS_TO_TICKS(50));
            } else {
                vTaskDelay(pdMS_TO_TICKS(20));
            }
            x_last = x;
            y_last = y; 

            //顺时针90度显示 要调整x y坐标
             printf("x_last=%d,y_last=%d\r\n",x_last,y_last);

            i2c_read_bytes(gslx6870_device, 0x80, touch_data, 8);

            gslx6870_deal(touch_data, &x, &y, &touched);
        }

        atomic_store(&touch_info.touched, false);
        xTaskNotifyWait(0x00, 0x00, NULL, pdMS_TO_TICKS(50)); 
    }
}

static void touch_gslx6870_init_task(uint8_t sda, uint8_t scl, int8_t intr_pin) {
    gslx6870_device = i2c_malloc_device(I2C_NUM_0, sda, scl, 400000, 0x40);
    i2c_device_set_reg_bits(gslx6870_device, I2C_REG_8BIT);
    static TaskHandle_t task_handle;
    xTaskCreatePinnedToCore(gslx6870_read_task, "touch", 3072, (void *)(intr_pin < 0), 10, &task_handle, 0);
    if(intr_pin > -1) {
    	printf("start intr_pin %d\r\n",intr_pin);

        gpio_pad_select_gpio(intr_pin);
        gpio_set_direction(intr_pin, GPIO_MODE_INPUT);
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
        gpio_set_intr_type(intr_pin, GPIO_INTR_NEGEDGE);
        gpio_isr_handler_add(intr_pin, touch_isr_handler, task_handle);
    }
}

void gslx680_init(int8_t sda, int8_t scl, int8_t intr_pin, int8_t rst_pin) {
    if (rst_pin > -1) {
        gpio_pad_select_gpio(rst_pin);
        gpio_set_direction(rst_pin, GPIO_MODE_OUTPUT);

        gpio_set_level(rst_pin, 0);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(rst_pin, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    touch_gslx6870_init_task(sda, scl, intr_pin);
}

void gslx680_read_status(uint16_t* x, uint16_t* y, uint8_t* touched) {
#if CONFIG_EXAMPLE_BOARD_1
	//顺时针90度显示 要调整x y坐标
    *x = atomic_load(&touch_info.y);
    *y = 320-atomic_load(&touch_info.x);
    *touched = atomic_load(&touch_info.touched);
#else
    *x = atomic_load(&touch_info.x);
    *y = atomic_load(&touch_info.y);
    *touched = atomic_load(&touch_info.touched);
#endif
}
