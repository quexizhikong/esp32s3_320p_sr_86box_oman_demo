/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_timer.h"
#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_chip_info.h"
#include "esp_spi_flash.h"
#include "sdkconfig.h"
#include "nvs_flash.h"

#include "bsp_storage.h"
#include "app_sr.h"
#include "app_player.h"
#include "user_board.h"
#include "qmsd_api.h"

#include "ESP32_Clock.h"


static const char *TAG = "main";



#ifdef CONFIG_FREERTOS_USE_TRACE_FACILITY
char pWriteBuffer[1024];
#endif

void monitorTask(void *pvParameter)
{
//	lv_mem_monitor_t mon;

	while(1)
	{
		vTaskDelay(2000 / portTICK_PERIOD_MS);

//		lv_mem_monitor(&mon);
//		ESP_LOGI(TAG,"used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
//		          mon.used_pct,
//		          mon.frag_pct,
//		          (int)mon.free_biggest_size);

		ESP_LOGI(TAG,"-INTERNAL RAM left %dKB",heap_caps_get_free_size( MALLOC_CAP_INTERNAL )/1024);
		#ifdef CONFIG_SPIRAM
		ESP_LOGI(TAG,"-     SPI RAM left %dkB",heap_caps_get_free_size( MALLOC_CAP_SPIRAM )/1024);
		#endif

		#ifdef CONFIG_FREERTOS_USE_TRACE_FACILITY
		vTaskList((char *)&pWriteBuffer);
		printf("\r\n任务名       任务状态 优先级   剩余栈 任务序号\r\n");
		printf("%s\r\n", pWriteBuffer);
		#endif
	}
}


void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    esp_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

   // qmsd_nvs_init();
    ESP_ERROR_CHECK(bsp_spiffs_init("storage", "/spiffs", 2));

    qmsd_board_hw_init();
    qmsd_ui_init();

    xTaskCreate(&monitorTask, "montask", 3072, NULL,2,NULL);
//	xTaskCreate(&esp32TimeTask, "rtc", 3072, NULL,3,NULL);

//	//eth_init_sta();

////test mp3
//    ESP_ERROR_CHECK(app_player_start("/spiffs/mp3"));

//esr esp-asr
	app_sr_model_init();
	app_sr_init();

}
