#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "screen_driver.h"
#include "user_board.h"
#include "board_pin.h"
//#include "qmsd_ui_entry.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "esp_lcd_panel_gs_st7796.h"
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_demos.h"
#else
#include "lvgl/lvgl.h"
#include "demos/lv_demos.h"
#endif
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "qmsd_api.h"
#include "sdkconfig.h"


#define TAG "QMSD_BOARD"


lv_ui guider_ui;


void qmsd_ui_entry(void);


#define PIXEL_TO_SIZE(v) ((v) * sizeof(lv_color_t))
#define QMSD_DIS_BUF    (320 * 320)

#ifdef CONFIG_EXAMPLE_LCD_I80_CONTROLLER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if CONFIG_EXAMPLE_LCD_I80_COLOR_IN_PSRAM
// PCLK frequency can't go too high as the limitation of PSRAM bandwidth
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (8 * 1000 * 1000)
#else
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (8 * 1000 * 1000)
#endif // CONFIG_EXAMPLE_LCD_I80_COLOR_IN_PSRAM
// Bit number used to represent command and parameter
#if CONFIG_EXAMPLE_LCD_I80_CONTROLLER_ST7789
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8
#elif CONFIG_EXAMPLE_LCD_I80_CONTROLLER_ST7796
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8
#elif CONFIG_EXAMPLE_LCD_I80_CONTROLLER_ILI9488
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8
#endif

// Supported alignment: 16, 32, 64. A higher alignment can enables higher burst transfer size, thus a higher i80 bus throughput.
#define EXAMPLE_PSRAM_DATA_ALIGNMENT   64
#endif

scr_driver_t *g_lcd;
extern void gslx680_init(int8_t sda, int8_t scl, int8_t intr_pin, int8_t rst_pin);
extern void gslx680_read_status(uint16_t* x, uint16_t* y, uint8_t* touched);

#ifdef CONFIG_EXAMPLE_LCD_I80_CONTROLLER
static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}
static void my_lvgl_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}
#else
QueueHandle_t image_queue;

typedef struct  {
    int offsetx1;
    int offsetx2;
    int offsety1;
    int offsety2;
    lv_color_t* color;
    lv_disp_drv_t *drv;
} show_data_t;

void show_bitmap(void *arg) {
    (void)arg;
    show_data_t* show_data;
    for (;;) {
        if (xQueueReceive(image_queue, &show_data, portMAX_DELAY) == pdTRUE) {
            int offsetx1 = show_data->offsetx1;
            int w = show_data->offsetx2 - show_data->offsetx1 + 1;
            int offsety1 = show_data->offsety1;
            int h = show_data->offsety2 - show_data->offsety1 + 1;
            g_lcd->draw_bitmap(offsetx1, offsety1, w, h, (uint16_t *)show_data->color);
            lv_disp_flush_ready(show_data->drv);
            free(show_data);
        }
    }
}

static void my_lvgl_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    show_data_t* show_data = (show_data_t*)heap_caps_calloc(1, sizeof(show_data_t), MALLOC_CAP_DEFAULT | MALLOC_CAP_INTERNAL);
    show_data->drv = drv;
    show_data->offsetx1 = area->x1;
    show_data->offsetx2 = area->x2;
    show_data->offsety1 = area->y1;
    show_data->offsety2 = area->y2;
    show_data->color = color_map;
    xQueueSend(image_queue, &show_data, portMAX_DELAY);
}
static void IRAM_ATTR gpio_isr_handler(void* arg) {
    SemaphoreHandle_t frame_semphr = (SemaphoreHandle_t)arg;
    int higher_priority_task_awoken = pdFALSE;
    xSemaphoreGiveFromISR(frame_semphr, &higher_priority_task_awoken);
    if (higher_priority_task_awoken) {
        portYIELD_FROM_ISR();
    }
}
#endif


void qmsd_disp_wait(uint32_t x, uint32_t y)
{

}

#if(LVGL_VERSION_MAJOR >7)
void touchpad_gslx680_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    uint16_t tp_x, tp_y;
    uint8_t press;
    gslx680_read_status(&tp_x, &tp_y, &press);
    data->state = press;
    data->point.x = tp_x;
    data->point.y = tp_y;
}
#else
bool touchpad_gslx680_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    uint16_t tp_x, tp_y;
    uint8_t press;
    gslx680_read_status(&tp_x, &tp_y, &press);
    data->state = press;
    data->point.x = tp_x;
    data->point.y = tp_y;
    return false;
}
#endif

////void qmsd_screen_init(SemaphoreHandle_t semaphore)
//void qmsd_screen_init(SemaphoreHandle_t semaphore)
//{
//
//}

#define LV_TICK_PERIOD_MS 2

static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

///* Creates a semaphore to handle concurrent call to lvgl stuff
// * If you wish to call *any* lvgl function from other threads/tasks
// * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

static void guiTask(void *pvParameter)
{
//    static lv_disp_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
//    static lv_disp_drv_t disp_drv;      // contains callback functions
//
    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    static lv_disp_drv_t disp_drv;      // contains callback functions

#ifdef CONFIG_EXAMPLE_LCD_I80_CONTROLLER
    (void) pvParameter;

    ESP_LOGI(TAG, "Initialize Intel 8080 bus");
    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .clk_src = LCD_CLK_SRC_PLL160M,
        .dc_gpio_num = LCD_RS_PIN,
        .wr_gpio_num = LCD_WR_PIN,
        .data_gpio_nums = {
                LCD_D0_PIN,
                LCD_D1_PIN,
                LCD_D2_PIN,
                LCD_D3_PIN,
                LCD_D4_PIN,
                LCD_D5_PIN,
                LCD_D6_PIN,
                LCD_D7_PIN,
        },
        .bus_width = CONFIG_EXAMPLE_LCD_I80_BUS_WIDTH,
        .max_transfer_bytes = LCD_WIDTH * 100 * sizeof(uint16_t),
        .psram_trans_align = EXAMPLE_PSRAM_DATA_ALIGNMENT,
        .sram_trans_align = 4,
    };
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = LCD_CS_PIN,
        .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
        .flags = {
            .swap_color_bytes = !LV_COLOR_16_SWAP, // Swap can be done in LvGL (default) or DMA
        },
        .on_color_trans_done = example_notify_lvgl_flush_ready,
        .user_ctx = &disp_drv,
        .lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,
        .lcd_param_bits = EXAMPLE_LCD_PARAM_BITS,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;

    ESP_LOGI(TAG, "Install LCD driver of st7789");
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RESET_PIN,
        .color_space =ESP_LCD_COLOR_SPACE_BGR ,// ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_gs_st7796(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);

    //esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_invert_color(panel_handle, true);

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();


    void *buf1 = NULL;
    ESP_LOGI(TAG, "Allocate separate LVGL draw buffers from RAM");
    buf1 = heap_caps_malloc( 320 * 40 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

    assert(buf1);
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, 320 * 40);

    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
//    lv_color_t *buf1 = NULL;
//    lv_color_t *buf2 = NULL;
//#if CONFIG_EXAMPLE_LCD_I80_COLOR_IN_PSRAM
//    buf1 = heap_caps_aligned_alloc(EXAMPLE_PSRAM_DATA_ALIGNMENT, 320 * 100 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
//#else
//    buf1 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
//#endif
//    assert(buf1);
//#if CONFIG_EXAMPLE_LCD_I80_COLOR_IN_PSRAM
//    buf2 = heap_caps_aligned_alloc(EXAMPLE_PSRAM_DATA_ALIGNMENT, 320 * 100 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
//#else
//    buf2 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
//#endif
//    assert(buf2);
//    ESP_LOGI(TAG, "buf1@%p, buf2@%p", buf1, buf2);
//    // initialize LVGL draw buffers
//    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, 320 * 100);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_HIGHT;
    disp_drv.ver_res = LCD_WIDTH;
    //disp_drv.flush_cb = example_lvgl_flush_cb;
	disp_drv.flush_cb = my_lvgl_flush; /*Used in buffered mode (LV_VDB_SIZE != 0  in lv_conf.h)*/
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    //lv_disp_t *disp=lv_disp_drv_register(&disp_drv);
    lv_disp_drv_register(&disp_drv);
#else
    ESP_LOGI(TAG, "Initialize i2s lcd");

	//SemaphoreHandle_t semaphore=(SemaphoreHandle_t)pvParameter;

#ifdef LCD_RD_PIN
    if (LCD_RD_PIN > -1) {
        gpio_pad_select_gpio(LCD_RD_PIN);
        gpio_set_direction(LCD_RD_PIN, GPIO_MODE_OUTPUT);
        gpio_set_level(LCD_RD_PIN, 1);
        ESP_LOGI(TAG, "RD = 1");
    }
#endif

    i2s_lcd_config_t i2s_lcd_cfg = {
        .data_width = 8,
        .pin_data_num = {
            LCD_D0_PIN,
            LCD_D1_PIN,
            LCD_D2_PIN,
            LCD_D3_PIN,
            LCD_D4_PIN,
            LCD_D5_PIN,
            LCD_D6_PIN,
            LCD_D7_PIN,
        },
        .pin_num_cs = -1,//LCD_CS_PIN,
        .pin_num_wr = LCD_WR_PIN,
        .pin_num_rs = LCD_RS_PIN,
        .clk_freq = 20000000,
        .i2s_port = I2S_NUM_0,
        .buffer_size = 8000,
        .swap_data = true,
    };

    scr_interface_driver_t *iface_drv;
    scr_interface_create(SCREEN_IFACE_8080, &i2s_lcd_cfg, &iface_drv);
    extern scr_driver_t lcd_gs_st7796_default_driver;
    g_lcd = &lcd_gs_st7796_default_driver;

    scr_controller_config_t lcd_cfg = {
        .interface_drv = iface_drv,
        .pin_num_rst = -1,
        .pin_num_bckl = -1,
        .rst_active_level = 0,
        .bckl_active_level = 1,
        .offset_hor = 0,
        .offset_ver = 0,
        .width = LCD_WIDTH,
        .height = LCD_HIGHT,
        .rotate = SCR_DIR_LRTB,
    };

    lcd_cfg.rotate = SCR_MIRROR_X;
    g_lcd->init(&lcd_cfg);

//    if (LCD_TE_PIN >=0) {
//        gpio_pad_select_gpio(LCD_TE_PIN);
//        gpio_set_direction(LCD_TE_PIN, GPIO_MODE_INPUT);
//        if (semaphore) {
//            gpio_set_intr_type(LCD_TE_PIN, GPIO_INTR_POSEDGE);
//            gpio_isr_handler_add(LCD_TE_PIN, gpio_isr_handler, semaphore);
//        }
//    }

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

	lv_color_t* buf1 = heap_caps_malloc(320*80 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
	lv_color_t* buf2 = heap_caps_malloc(320*80 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);//
	lv_disp_draw_buf_init(&disp_buf, buf1, buf2, 320*80);

//	lv_disp_drv_init(&disp_drv);
//	disp_drv.hor_res = LCD_HIGHT;
//	disp_drv.ver_res = LCD_WIDTH;
//	disp_drv.flush_cb = my_lvgl_flush; /*Used in buffered mode (LV_VDB_SIZE != 0  in lv_conf.h)*/
//	/* Finally register the driver */
//	lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_HIGHT;
    disp_drv.ver_res = LCD_WIDTH;
    //disp_drv.flush_cb = example_lvgl_flush_cb;
	disp_drv.flush_cb = my_lvgl_flush; /*Used in buffered mode (LV_VDB_SIZE != 0  in lv_conf.h)*/
    disp_drv.draw_buf = &disp_buf;
    //lv_disp_t *disp=lv_disp_drv_register(&disp_drv);
    lv_disp_drv_register(&disp_drv);

	image_queue = xQueueCreate(1, sizeof(show_data_t*));
	xTaskCreatePinnedToCore(show_bitmap, "show bitmap", 4 * 1024, NULL, 2, NULL, 0);
#endif

	lv_indev_drv_t indev_drv;               /*Descriptor of an input device driver*/
	lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
	indev_drv.type = LV_INDEV_TYPE_POINTER; /*The touchpad is pointer type device*/
	indev_drv.read_cb = &touchpad_gslx680_read;            /*Library ready your touchpad via this function*/
	lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/

	/* Create and start a periodic timer interrupt to call lv_tick_inc */
	const esp_timer_create_args_t periodic_timer_args = {
		.callback = &lv_tick_task,
		.name = "lvgl_tick"
	};
	esp_timer_handle_t periodic_timer;
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
	ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

	qmsd_ui_entry();

	qmsd_backlight_control(100);

	while (1)
	{
		/* Delay 1 tick (assumes FreeRTOS tick is 10ms */
		vTaskDelay(pdMS_TO_TICKS(10));

		/* Try to take the semaphore, call lvgl related function on success */
		if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))//获取信号量
		{
			lv_task_handler();
			xSemaphoreGive(xGuiSemaphore);//释放信号量
		}
	}
}

TaskHandle_t pvguiTaskTask=NULL;

void qmsd_ui_init(void)
{
	xGuiSemaphore = xSemaphoreCreateMutex();

	gslx680_init(TOUCH_IIC_SDA, TOUCH_IIC_SCL, TOUCH_IIC_INT, TOUCH_RESET_PIN);

    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
  //  xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL,5, NULL, 1);
    xTaskCreate(&guiTask, "gui", 4096, NULL, 5, &pvguiTaskTask);
}
//线程互斥锁 必须在qmsd_board_init之后才能使用
int qmsd_gui_lock(uint32_t timeout)
{
	//return !xSemaphoreTake(xGuiSemaphore, timeout / portTICK_PERIOD_MS);//启明取反才对//获取信号量 成功返回 pdTRUE，否则返回 errQUEUE_EMPTY
	return xSemaphoreTake(xGuiSemaphore, timeout / portTICK_PERIOD_MS);//获取信号量 成功返回 pdTRUE，否则返回 errQUEUE_EMPTY
}
int qmsd_gui_unlock(void)
{
	return xSemaphoreGive(xGuiSemaphore);//释放信号量 成功返回 pdTRUE，否则返回 pdFALSE
}

void qmsd_ui_entry(void)
{
//////	//lv_demo_widgets();
//	lv_demo_benchmark();

//Create a GUI-Guider app
	memset(&guider_ui,0,sizeof(guider_ui));

	setup_ui(&guider_ui);
	events_init(&guider_ui);
	custom_init(&guider_ui);
}

