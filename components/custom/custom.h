// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif
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

#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"


#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "gui_guider.h"

extern lv_timer_t * animationtimer;
extern QueueHandle_t custom_rx_evt_queue;

void custom_init(lv_ui *ui);
void custom_task(void *pvParameter);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
