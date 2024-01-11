// Copyright 2020 Espressif Systems (Shanghai) Co. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "screen_driver.h"
#include "screen_utility.h"

#include "gs_st7796.h"

static const char *TAG = "gs_st7796";

#define LCD_CHECK(a, str, ret)  if(!(a)) {                               \
        ESP_LOGE(TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);   \
        return (ret);                                                           \
    }


#define LCD_NAME "GS_ST7796"
#define LCD_BPP  16

#define GS_ST7796_RESOLUTION_HOR 320
#define GS_ST7796_RESOLUTION_VER 480

/** commands of GS_ST7796 */
#define LCD_SWRESET 0x01  // Software Reset
#define LCD_RDDID   0x04  // Read Display ID
#define LCD_INVOFF  0x20  // Display Inversion Off
#define LCD_INVON   0x21  // Display Inversion On
#define LCD_CASET   0x2A  // Column Address Set
#define LCD_PASET   0x2B  // Row Address Set
#define LCD_RAMWR   0x2C  // Memory Writ
#define LCD_RAMRD   0x2E  // Memory Read
#define LCD_MADCTL  0x36  // Memory Data Access Control

/* MADCTL Defines */
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x08
#define MADCTL_MH  0x04

static scr_handle_t g_lcd_handle;

/**
 * This header file is only used to redefine the function to facilitate the call.
 * It can only be placed in this position, not in the head of the file.
 */
#include "interface_drv_def.h"

scr_driver_t lcd_gs_st7796_default_driver = {
    .init = lcd_gs_st7796_init,
    .deinit = lcd_gs_st7796_deinit,
    .set_direction = lcd_gs_st7796_set_rotation,
    .set_window = lcd_gs_st7796_set_window,
    .write_ram_data = lcd_gs_st7796_write_ram_data,
    .draw_pixel = lcd_gs_st7796_draw_pixel,
    .draw_bitmap = lcd_gs_st7796_draw_bitmap,
    .get_info = lcd_gs_st7796_get_info,
};


static esp_err_t lcd_gs_st7796_reg_config(void);

esp_err_t lcd_gs_st7796_init(const scr_controller_config_t *lcd_conf)
{
    LCD_CHECK(lcd_conf->width <= GS_ST7796_RESOLUTION_HOR, "Width greater than maximum", ESP_ERR_INVALID_ARG);
    LCD_CHECK(lcd_conf->height <= GS_ST7796_RESOLUTION_VER, "Height greater than maximum", ESP_ERR_INVALID_ARG);
    LCD_CHECK(NULL != lcd_conf, "config pointer invalid", ESP_ERR_INVALID_ARG);
    LCD_CHECK((NULL != lcd_conf->interface_drv->write_cmd && \
               NULL != lcd_conf->interface_drv->write_data && \
               NULL != lcd_conf->interface_drv->write && \
               NULL != lcd_conf->interface_drv->read && \
               NULL != lcd_conf->interface_drv->bus_acquire && \
               NULL != lcd_conf->interface_drv->bus_release),
              "Interface driver invalid", ESP_ERR_INVALID_ARG);
    esp_err_t ret;
    // Reset the display
    if (lcd_conf->pin_num_rst >= 0) {
        gpio_pad_select_gpio(lcd_conf->pin_num_rst);
        gpio_set_direction(lcd_conf->pin_num_rst, GPIO_MODE_OUTPUT);
        gpio_set_level(lcd_conf->pin_num_rst, (lcd_conf->rst_active_level) & 0x1);
        vTaskDelay(100 / portTICK_RATE_MS);
        gpio_set_level(lcd_conf->pin_num_rst, (~(lcd_conf->rst_active_level)) & 0x1);
        vTaskDelay(100 / portTICK_RATE_MS);
    }

    g_lcd_handle.interface_drv = lcd_conf->interface_drv;
    g_lcd_handle.original_width = lcd_conf->width;
    g_lcd_handle.original_height = lcd_conf->height;
    g_lcd_handle.offset_hor = lcd_conf->offset_hor;
    g_lcd_handle.offset_ver = lcd_conf->offset_ver;

    // Send all the commands
    ret = lcd_gs_st7796_reg_config();
    LCD_CHECK(ESP_OK == ret, "Write lcd register encounter error", ESP_FAIL);

    // Enable backlight
    if (lcd_conf->pin_num_bckl >= 0) {
        gpio_pad_select_gpio(lcd_conf->pin_num_bckl);
        gpio_set_direction(lcd_conf->pin_num_bckl, GPIO_MODE_OUTPUT);
        gpio_set_level(lcd_conf->pin_num_bckl, (lcd_conf->bckl_active_level) & 0x1);
    }
    ret = lcd_gs_st7796_set_rotation(lcd_conf->rotate);
    LCD_CHECK(ESP_OK == ret, "Set rotate failed", ESP_FAIL);
    lcd_gs_st7796_set_invert(true);

    return ESP_OK;
}

esp_err_t lcd_gs_st7796_deinit(void)
{
    memset(&g_lcd_handle, 0, sizeof(scr_handle_t));
    return ESP_OK;
}

esp_err_t lcd_gs_st7796_set_rotation(scr_dir_t dir)
{
    esp_err_t ret;
    uint8_t reg_data = 0;
    reg_data |= MADCTL_RGB;
    if (SCR_DIR_MAX < dir) {
        dir >>= 5;
    }
    LCD_CHECK(dir < 8, "Unsupport rotate direction", ESP_ERR_INVALID_ARG);
    switch (dir) {
    case SCR_DIR_LRTB:
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_LRBT:
        reg_data |= MADCTL_MY;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_RLTB:
        reg_data |= MADCTL_MX;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_RLBT:
        reg_data |= MADCTL_MX | MADCTL_MY;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;

    case SCR_DIR_TBLR:
        reg_data |= MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_BTLR:
        reg_data |= MADCTL_MY | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_TBRL:
        reg_data |= MADCTL_MX | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_BTRL:
        reg_data |= MADCTL_MX | MADCTL_MY | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    default: break;
    }
    ESP_LOGI(TAG, "MADCTL=%x", reg_data);
    ret = LCD_WRITE_REG(LCD_MADCTL, reg_data);
    LCD_CHECK(ESP_OK == ret, "Set screen rotate failed", ESP_FAIL);
    g_lcd_handle.dir = dir;
    return ESP_OK;
}

esp_err_t lcd_gs_st7796_get_info(scr_info_t *info)
{
    LCD_CHECK(NULL != info, "info pointer invalid", ESP_ERR_INVALID_ARG);
    info->width = g_lcd_handle.width;
    info->height = g_lcd_handle.height;
    info->dir = g_lcd_handle.dir;
    info->name = LCD_NAME;
    info->color_type = SCR_COLOR_TYPE_RGB565;
    info->bpp = LCD_BPP;
    return ESP_OK;
}

esp_err_t lcd_gs_st7796_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_CHECK((x1 < g_lcd_handle.width) && (y1 < g_lcd_handle.height), "The set coordinates exceed the screen size", ESP_ERR_INVALID_ARG);
    LCD_CHECK((x0 <= x1) && (y0 <= y1), "Window coordinates invalid", ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_OK;
    scr_utility_apply_offset(&g_lcd_handle, GS_ST7796_RESOLUTION_HOR, GS_ST7796_RESOLUTION_VER, &x0, &y0, &x1, &y1);

    ret |= LCD_WRITE_CMD(LCD_CASET);
    ret |= LCD_WRITE_DATA(x0 >> 8);
    ret |= LCD_WRITE_DATA(x0 & 0xff);
    ret |= LCD_WRITE_DATA(x1 >> 8);
    ret |= LCD_WRITE_DATA(x1 & 0xff);
    ret |= LCD_WRITE_CMD(LCD_PASET);
    ret |= LCD_WRITE_DATA(y0 >> 8);
    ret |= LCD_WRITE_DATA(y0 & 0xff);
    ret |= LCD_WRITE_DATA(y1 >> 8);
    ret |= LCD_WRITE_DATA(y1 & 0xff);

    ret |= LCD_WRITE_CMD(LCD_RAMWR);
    LCD_CHECK(ESP_OK == ret, "Set window failed", ESP_FAIL);
    return ESP_OK;
}


esp_err_t lcd_gs_st7796_write_ram_data(uint16_t color)
{
    static uint8_t data[2];
    data[0] = (uint8_t)(color & 0xff);
    data[1] = (uint8_t)(color >> 8);
    return LCD_WRITE(data, 2);
}

esp_err_t lcd_gs_st7796_set_invert(bool is_invert)
{
    return LCD_WRITE_CMD(is_invert ? LCD_INVON : LCD_INVOFF);
}

esp_err_t lcd_gs_st7796_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    esp_err_t ret;
    ret = lcd_gs_st7796_set_window(x, y, x, y);
    if (ESP_OK != ret) {
        return ESP_FAIL;
    }
    return lcd_gs_st7796_write_ram_data(color);
}

esp_err_t lcd_gs_st7796_draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    esp_err_t ret;
    LCD_CHECK(NULL != bitmap, "bitmap pointer invalid", ESP_ERR_INVALID_ARG);

    LCD_IFACE_ACQUIRE();
    ret = lcd_gs_st7796_set_window(x, y, x + w - 1, y + h - 1);
    if (ESP_OK != ret) {
        return ESP_FAIL;
    }

    uint32_t len = w * h;
    ret = LCD_WRITE((uint8_t *)bitmap, 2 * len);
    LCD_IFACE_RELEASE();
    LCD_CHECK(ESP_OK == ret, "lcd write ram data failed", ESP_FAIL);
    return ESP_OK;
}

static esp_err_t lcd_gs_st7796_reg_config(void)
{
    LCD_WRITE_CMD(0xF0);     
    LCD_WRITE_DATA(0xC3);   

    LCD_WRITE_CMD(0xF0);     
    LCD_WRITE_DATA(0x96);  

    LCD_WRITE_CMD(0x36);     
    LCD_WRITE_DATA(0x48);   

    LCD_WRITE_CMD(0x3A);     
    LCD_WRITE_DATA(0x55);   

    LCD_WRITE_CMD(0xB4);     
    LCD_WRITE_DATA(0x01);   

    LCD_WRITE_CMD(0xB1);     
    LCD_WRITE_DATA(0x80);   //FRS[D7-D4], DIVA[D1-D0] 81 for 15Hz
    LCD_WRITE_DATA(0x10);   //RTNA[4:0]

    LCD_WRITE_CMD(0xB5);     
    LCD_WRITE_DATA(0x1F);   //VFP FF for 15Hz
    LCD_WRITE_DATA(0x39);   //VBP FF for 15Hz
    LCD_WRITE_DATA(0x00);   
    LCD_WRITE_DATA(0x20);   //HBP

    LCD_WRITE_CMD(0xB6);     
    LCD_WRITE_DATA(0x80);   
    LCD_WRITE_DATA(0x00);   
    LCD_WRITE_DATA(0x27);   //320 Gates

    LCD_WRITE_CMD(0xB7);     
    LCD_WRITE_DATA(0xC6);   

    LCD_WRITE_CMD(0xC0);     
    LCD_WRITE_DATA(0xA0); 
    LCD_WRITE_DATA(0x07);    

    LCD_WRITE_CMD(0xC1);     
    LCD_WRITE_DATA(0x13);  //15 

    LCD_WRITE_CMD(0xC2);     
    LCD_WRITE_DATA(0xA7); //13  

    LCD_WRITE_CMD(0xC5);     
    LCD_WRITE_DATA(0x05);   //VCOM//09

    LCD_WRITE_CMD(0xE8);     
    LCD_WRITE_DATA(0x40);   
    LCD_WRITE_DATA(0x84);   
    LCD_WRITE_DATA(0x1D);   
    LCD_WRITE_DATA(0x21);   
    LCD_WRITE_DATA(0x28);   
    LCD_WRITE_DATA(0x13);   
    LCD_WRITE_DATA(0x3F);   
    LCD_WRITE_DATA(0x33);    

    LCD_WRITE_CMD(0xE0);     
    LCD_WRITE_DATA(0xF0);   
    LCD_WRITE_DATA(0x17);   
    LCD_WRITE_DATA(0x1B);   
    LCD_WRITE_DATA(0x0B);   
    LCD_WRITE_DATA(0x0A);   
    LCD_WRITE_DATA(0x08);   
    LCD_WRITE_DATA(0x37);   
    LCD_WRITE_DATA(0x44);   
    LCD_WRITE_DATA(0x4B);   
    LCD_WRITE_DATA(0x3C);   
    LCD_WRITE_DATA(0x17);   
    LCD_WRITE_DATA(0x16);   
    LCD_WRITE_DATA(0x2E);   
    LCD_WRITE_DATA(0x35);   

    LCD_WRITE_CMD(0xE1);     
    LCD_WRITE_DATA(0xF0);   
    LCD_WRITE_DATA(0x1A);   
    LCD_WRITE_DATA(0x1D);   
    LCD_WRITE_DATA(0x08);   
    LCD_WRITE_DATA(0x06);   
    LCD_WRITE_DATA(0x10);   
    LCD_WRITE_DATA(0x37);   
    LCD_WRITE_DATA(0x33);   
    LCD_WRITE_DATA(0x4A);   
    LCD_WRITE_DATA(0x32);   
    LCD_WRITE_DATA(0x10);   
    LCD_WRITE_DATA(0x11);   
    LCD_WRITE_DATA(0x29);   
    LCD_WRITE_DATA(0x31); 

    LCD_WRITE_CMD(0xF0);     
    LCD_WRITE_DATA(0x3C);   

    LCD_WRITE_CMD(0xF0);     
    LCD_WRITE_DATA(0x69);   

    LCD_WRITE_CMD(0x21);

    LCD_WRITE_CMD(0x11);
    vTaskDelay(pdMS_TO_TICKS(120)); 
    LCD_WRITE_CMD(0x29);

    LCD_WRITE_CMD(0x2C);

    return ESP_OK;
}