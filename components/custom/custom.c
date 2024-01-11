// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>

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
#include "esp_wifi.h"
#include "esp_event.h"
#include "driver/gpio.h"

#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "cJSON.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


#define TAG "custom"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
QueueHandle_t custom_rx_evt_queue = NULL;

extern SemaphoreHandle_t xGuiSemaphore;
/**
 * Create a demo application
 */
void custom_task(void *pvParameter);

void custom_init(lv_ui *ui)
{
    /* Add your codes here */

	custom_rx_evt_queue = xQueueCreate(5, sizeof(char));
    if(custom_rx_evt_queue)
    {
    	ESP_LOGI(TAG,"custom_init create suss!");
    }
    else
    {
    	ESP_LOGI(TAG,"custom_init create fail!");
    }
    xTaskCreate(&custom_task, "custom", 4096, NULL,5,NULL);
}
void custom_task(void *pvParameter)
{
	char evt;

	for(;;)
	{
		if( xQueueReceive(custom_rx_evt_queue, &evt,portMAX_DELAY) == pdPASS )
		{
			/* Try to take the semaphore, call lvgl related function on success */
			if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
			{
				switch(evt)
				{
					case 1://wake
					{
						ESP_LOGI(TAG,"wake");

						if(!guider_ui.voiceauto_screen)
						{
							setup_scr_voiceauto_screen(&guider_ui);
							//lv_scr_load(guider_ui.voiceauto_screen);
						}
					}
					break;
					case 2://detected
					{
						ESP_LOGI(TAG,"detected");

						if(guider_ui.voiceauto_screen)
						{
							lv_obj_del(guider_ui.voiceauto_screen);
							guider_ui.voiceauto_screen=NULL;
						}
					}
					break;
					case 3://timeout
					{
						ESP_LOGI(TAG,"timeout");

						if(guider_ui.voiceauto_screen)
						{
							lv_obj_del(guider_ui.voiceauto_screen);
							guider_ui.voiceauto_screen=NULL;
						}
					}
					break;
					default:
					break;
				}

				xSemaphoreGive(xGuiSemaphore);
			}
		}
	}
}
