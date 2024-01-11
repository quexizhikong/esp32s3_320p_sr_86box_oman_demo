/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <stdlib.h>
#include <sys/cdefs.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_commands.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

static const char *TAG = "gs_st7796";

static esp_err_t panel_gs_st7796_del(esp_lcd_panel_t *panel);
static esp_err_t panel_gs_st7796_reset(esp_lcd_panel_t *panel);
static esp_err_t panel_gs_st7796_init(esp_lcd_panel_t *panel);
static esp_err_t panel_gs_st7796_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data);
static esp_err_t panel_gs_st7796_invert_color(esp_lcd_panel_t *panel, bool invert_color_data);
static esp_err_t panel_gs_st7796_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y);
static esp_err_t panel_gs_st7796_swap_xy(esp_lcd_panel_t *panel, bool swap_axes);
static esp_err_t panel_gs_st7796_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap);
static esp_err_t panel_gs_st7796_disp_off(esp_lcd_panel_t *panel, bool off);

typedef struct {
    esp_lcd_panel_t base;
    esp_lcd_panel_io_handle_t io;
    int reset_gpio_num;
    bool reset_level;
    int x_gap;
    int y_gap;
    uint8_t fb_bits_per_pixel;
    uint8_t madctl_val; // save current value of LCD_CMD_MADCTL register
    uint8_t colmod_cal; // save surrent value of LCD_CMD_COLMOD register
} gs_st7796_panel_t;

esp_err_t esp_lcd_new_panel_gs_st7796(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel)
{
    esp_err_t ret = ESP_OK;
    gs_st7796_panel_t *gs_st7796 = NULL;
    ESP_GOTO_ON_FALSE(io && panel_dev_config && ret_panel, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    gs_st7796 = calloc(1, sizeof(gs_st7796_panel_t));
    ESP_GOTO_ON_FALSE(gs_st7796, ESP_ERR_NO_MEM, err, TAG, "no mem for gs_st7796 panel");

    if (panel_dev_config->reset_gpio_num >= 0) {
        gpio_config_t io_conf = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << panel_dev_config->reset_gpio_num,
        };
        ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configure GPIO for RST line failed");
    }

    switch (panel_dev_config->color_space) {
    case ESP_LCD_COLOR_SPACE_RGB:
        gs_st7796->madctl_val = 0;
        break;
    case ESP_LCD_COLOR_SPACE_BGR:
        gs_st7796->madctl_val |= LCD_CMD_BGR_BIT;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported color space");
        break;
    }

    uint8_t fb_bits_per_pixel = 0;
    switch (panel_dev_config->bits_per_pixel) {
    case 16: // RGB565
        gs_st7796->colmod_cal = 0x55;
        fb_bits_per_pixel = 16;
        break;
    case 18: // RGB666
        gs_st7796->colmod_cal = 0x66;
        // each color component (R/G/B) should occupy the 6 high bits of a byte, which means 3 full bytes are required for a pixel
        fb_bits_per_pixel = 24;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported pixel width");
        break;
    }

    gs_st7796->io = io;
    gs_st7796->fb_bits_per_pixel = fb_bits_per_pixel;
    gs_st7796->reset_gpio_num = panel_dev_config->reset_gpio_num;
    gs_st7796->reset_level = panel_dev_config->flags.reset_active_high;
    gs_st7796->base.del = panel_gs_st7796_del;
    gs_st7796->base.reset = panel_gs_st7796_reset;
    gs_st7796->base.init = panel_gs_st7796_init;
    gs_st7796->base.draw_bitmap = panel_gs_st7796_draw_bitmap;
    gs_st7796->base.invert_color = panel_gs_st7796_invert_color;
    gs_st7796->base.set_gap = panel_gs_st7796_set_gap;
    gs_st7796->base.mirror = panel_gs_st7796_mirror;
    gs_st7796->base.swap_xy = panel_gs_st7796_swap_xy;
    gs_st7796->base.disp_off = panel_gs_st7796_disp_off;
    *ret_panel = &(gs_st7796->base);
    ESP_LOGI(TAG, "new gs_st7796 panel @%p", gs_st7796);

    return ESP_OK;

err:
    if (gs_st7796) {
        if (panel_dev_config->reset_gpio_num >= 0) {
            gpio_reset_pin(panel_dev_config->reset_gpio_num);
        }
        free(gs_st7796);
    }
    return ret;
}

static esp_err_t panel_gs_st7796_del(esp_lcd_panel_t *panel)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);

    if (gs_st7796->reset_gpio_num >= 0) {
        gpio_reset_pin(gs_st7796->reset_gpio_num);
    }
    ESP_LOGI(TAG, "del gs_st7796 panel @%p", gs_st7796);
    free(gs_st7796);
    return ESP_OK;
}

static esp_err_t panel_gs_st7796_reset(esp_lcd_panel_t *panel)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;

    // perform hardware reset
    if (gs_st7796->reset_gpio_num >= 0) {
        gpio_set_level(gs_st7796->reset_gpio_num, gs_st7796->reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(gs_st7796->reset_gpio_num, !gs_st7796->reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
    } else { // perform software reset
        esp_lcd_panel_io_tx_param(io, LCD_CMD_SWRESET, NULL, 0);
        vTaskDelay(pdMS_TO_TICKS(20)); // spec, wait at least 5m before sending new command
    }

    return ESP_OK;
}

static esp_err_t panel_gs_st7796_init(esp_lcd_panel_t *panel)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;
    // LCD goes into sleep mode and display will be turned off after power on reset, exit sleep mode first
    esp_lcd_panel_io_tx_param(io, LCD_CMD_SLPOUT, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, (uint8_t[]) {
        gs_st7796->madctl_val,
    }, 1);
    esp_lcd_panel_io_tx_param(io, LCD_CMD_COLMOD, (uint8_t[]) {
        gs_st7796->colmod_cal,
    }, 1);

    esp_lcd_panel_io_tx_param(io, 0xF0, (uint8_t[]) { 0xC3 }, 1);
    esp_lcd_panel_io_tx_param(io, 0xF0, (uint8_t[]) { 0x96 }, 1);
    esp_lcd_panel_io_tx_param(io, 0x36, (uint8_t[]) { 0x48 }, 1);
    esp_lcd_panel_io_tx_param(io, 0x3A, (uint8_t[]) { 0x55 }, 1);
    esp_lcd_panel_io_tx_param(io, 0xB4, (uint8_t[]) { 0x01 }, 1);
    esp_lcd_panel_io_tx_param(io, 0xB1, (uint8_t[]) { 0x80,0x10 }, 2);

    esp_lcd_panel_io_tx_param(io, 0xB5, (uint8_t[]) { 0x1F,0x39,0x00,0x20 }, 4);
    esp_lcd_panel_io_tx_param(io, 0xB6, (uint8_t[]) { 0x80,0x00,0x27 }, 3);

    esp_lcd_panel_io_tx_param(io, 0xB7, (uint8_t[]) { 0xC6 }, 1);

    esp_lcd_panel_io_tx_param(io, 0xC0, (uint8_t[]) { 0xA0,0x07 }, 2);
    esp_lcd_panel_io_tx_param(io, 0xC1, (uint8_t[]) { 0x13 }, 1);
    esp_lcd_panel_io_tx_param(io, 0xC2, (uint8_t[]) { 0xA7 }, 1);
    esp_lcd_panel_io_tx_param(io, 0xC5, (uint8_t[]) { 0x05 }, 1);

    esp_lcd_panel_io_tx_param(io, 0xE8, (uint8_t[]) { 0x40,0x84,0x1D,0x21,0x28,0x13,0x3F,0x33 }, 8);

    esp_lcd_panel_io_tx_param(io, 0xE0, (uint8_t[]) {          // Set positive gamma
    	0xF0,0x17,0x1B,0x0B,0x0A,0x08,0x37,0x44,0x4B,0x3C,0x17,0x16,0x2E,0x35  }, 14);
    esp_lcd_panel_io_tx_param(io, 0xE1, (uint8_t[]) {          // Set negative gamma
    	0xF0,0x1A,0x1D,0x08,0x06,0x10,0x37,0x33,0x4A,0x32,0x10,0x11 ,0x29,0x31 }, 14);

    esp_lcd_panel_io_tx_param(io, 0xF0, (uint8_t[]) { 0x3C }, 1);
    esp_lcd_panel_io_tx_param(io, 0xF0, (uint8_t[]) { 0x96 }, 1);

    esp_lcd_panel_io_tx_param(io, 0x21, NULL, 0);
    esp_lcd_panel_io_tx_param(io, 0x11, NULL, 0);

    vTaskDelay(pdMS_TO_TICKS(120));

    esp_lcd_panel_io_tx_param(io, 0x29, NULL, 0);
    esp_lcd_panel_io_tx_param(io, 0x2C, NULL, 0);

    ESP_LOGI(TAG, "panel_init");

    return ESP_OK;
}

static esp_err_t panel_gs_st7796_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    assert((x_start < x_end) && (y_start < y_end) && "start position must be smaller than end position");
    esp_lcd_panel_io_handle_t io = gs_st7796->io;

    x_start += gs_st7796->x_gap;
    x_end += gs_st7796->x_gap;
    y_start += gs_st7796->y_gap;
    y_end += gs_st7796->y_gap;

    // define an area of frame memory where MCU can access
    esp_lcd_panel_io_tx_param(io, LCD_CMD_CASET, (uint8_t[]) {
        (x_start >> 8) & 0xFF,
        x_start & 0xFF,
        ((x_end - 1) >> 8) & 0xFF,
        (x_end - 1) & 0xFF,
    }, 4);
    esp_lcd_panel_io_tx_param(io, LCD_CMD_RASET, (uint8_t[]) {
        (y_start >> 8) & 0xFF,
        y_start & 0xFF,
        ((y_end - 1) >> 8) & 0xFF,
        (y_end - 1) & 0xFF,
    }, 4);
    // transfer frame buffer
    size_t len = (x_end - x_start) * (y_end - y_start) * gs_st7796->fb_bits_per_pixel / 8;
    esp_lcd_panel_io_tx_color(io, LCD_CMD_RAMWR, color_data, len);

    return ESP_OK;
}

static esp_err_t panel_gs_st7796_invert_color(esp_lcd_panel_t *panel, bool invert_color_data)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;
    int command = 0;
    if (invert_color_data) {
        command = LCD_CMD_INVON;
    } else {
        command = LCD_CMD_INVOFF;
    }
    esp_lcd_panel_io_tx_param(io, command, NULL, 0);
    return ESP_OK;
}

static esp_err_t panel_gs_st7796_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;
    if (mirror_x) {
        gs_st7796->madctl_val |= LCD_CMD_MX_BIT;
    } else {
        gs_st7796->madctl_val &= ~LCD_CMD_MX_BIT;
    }
    if (mirror_y) {
        gs_st7796->madctl_val |= LCD_CMD_MY_BIT;
    } else {
        gs_st7796->madctl_val &= ~LCD_CMD_MY_BIT;
    }
    esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, (uint8_t[]) {
        gs_st7796->madctl_val
    }, 1);
    return ESP_OK;
}

static esp_err_t panel_gs_st7796_swap_xy(esp_lcd_panel_t *panel, bool swap_axes)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;
    if (swap_axes) {
        gs_st7796->madctl_val |= LCD_CMD_MV_BIT;
    } else {
        gs_st7796->madctl_val &= ~LCD_CMD_MV_BIT;
    }
    esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, (uint8_t[]) {
        gs_st7796->madctl_val
    }, 1);
    return ESP_OK;
}

static esp_err_t panel_gs_st7796_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    gs_st7796->x_gap = x_gap;
    gs_st7796->y_gap = y_gap;
    return ESP_OK;
}

static esp_err_t panel_gs_st7796_disp_off(esp_lcd_panel_t *panel, bool off)
{
    gs_st7796_panel_t *gs_st7796 = __containerof(panel, gs_st7796_panel_t, base);
    esp_lcd_panel_io_handle_t io = gs_st7796->io;
    int command = 0;
    if (off) {
        command = LCD_CMD_DISPOFF;
    } else {
        command = LCD_CMD_DISPON;
    }
    esp_lcd_panel_io_tx_param(io, command, NULL, 0);
    return ESP_OK;
}
