
#ifndef __USER_BOARD_H__
#define __USER_BOARD_H__

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
#include "esp_timer.h"
#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"

#include "board_pin.h"
#include "driver/ledc.h"
#include "esxxx_common.h"
#include "audio_hal.h"
#include "qmsd_board_init.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#define BOARD "cGS01"

#define LCD_BK_LIGHT_ON_LEVEL  1

#define BOARD_LEDC_TIMER              LEDC_TIMER_3
#define BOARD_LEDC_MODE               LEDC_LOW_SPEED_MODE
#define BOARD_LEDC_CHANNEL            LEDC_CHANNEL_5
#define BOARD_LEDC_DUTY_RES           LEDC_TIMER_10_BIT // Set duty resolution to 10 bits
#define BOARD_LEDC_FREQUENCY          (500) // Frequency in Hertz. Set frequency at 1 kHz

#define CODEC_ADC_SAMPLE_RATE 16000
#define CODEC_ADC_BITS_PER_SAMPLE I2S_BITS_PER_SAMPLE_16BIT

extern audio_hal_func_t* audio_hal;

void qmsd_board_hw_init();

// 0 ~ 100
void qmsd_backlight_control(uint8_t light);

int board_get_feed_channel(void);

esp_err_t board_get_feed_data(int16_t *buffer, int chunksize);

void qmsd_ui_init(void);
void ir_test_demo(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*__USER_BOARD_H__*/
