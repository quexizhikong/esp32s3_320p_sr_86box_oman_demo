/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_device_rgblight(lv_ui *ui)
{
	//Write codes device_rgblight
	ui->device_rgblight = lv_obj_create(NULL);
	lv_obj_set_size(ui->device_rgblight, 320, 320);

	//Write style for device_rgblight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_return_img
	ui->device_rgblight_return_img = lv_img_create(ui->device_rgblight);
	lv_obj_add_flag(ui->device_rgblight_return_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->device_rgblight_return_img, &_returnbg_alpha_28x22);
	lv_img_set_pivot(ui->device_rgblight_return_img, 0,0);
	lv_img_set_angle(ui->device_rgblight_return_img, 0);
	lv_obj_set_pos(ui->device_rgblight_return_img, 10, 8);
	lv_obj_set_size(ui->device_rgblight_return_img, 28, 22);

	//Write style for device_rgblight_return_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->device_rgblight_return_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_return_imgbtn
	ui->device_rgblight_return_imgbtn = lv_btn_create(ui->device_rgblight);
	ui->device_rgblight_return_imgbtn_label = lv_label_create(ui->device_rgblight_return_imgbtn);
	lv_label_set_text(ui->device_rgblight_return_imgbtn_label, "");
	lv_label_set_long_mode(ui->device_rgblight_return_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_rgblight_return_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_rgblight_return_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_rgblight_return_imgbtn, 5, 5);
	lv_obj_set_size(ui->device_rgblight_return_imgbtn, 60, 32);

	//Write style for device_rgblight_return_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_return_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_return_imgbtn, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_return_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_light_sw
	ui->device_rgblight_light_sw = lv_switch_create(ui->device_rgblight);
	lv_obj_set_pos(ui->device_rgblight_light_sw, 26, 53);
	lv_obj_set_size(ui->device_rgblight_light_sw, 50, 22);

	//Write style for device_rgblight_light_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_light_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_light_sw, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_light_sw, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_light_sw, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_light_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_light_sw, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_light_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for device_rgblight_light_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->device_rgblight_light_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->device_rgblight_light_sw, lv_color_hex(0xffaa23), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_light_sw, LV_GRAD_DIR_VER, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_light_sw, lv_color_hex(0xffaa23), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->device_rgblight_light_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style for device_rgblight_light_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_light_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_light_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_light_sw, LV_GRAD_DIR_VER, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_light_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_light_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_light_sw, 100, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes device_rgblight_color_btn_1
	ui->device_rgblight_color_btn_1 = lv_btn_create(ui->device_rgblight);
	ui->device_rgblight_color_btn_1_label = lv_label_create(ui->device_rgblight_color_btn_1);
	lv_label_set_text(ui->device_rgblight_color_btn_1_label, "");
	lv_label_set_long_mode(ui->device_rgblight_color_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_rgblight_color_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_rgblight_color_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_rgblight_color_btn_1, 16, 90);
	lv_obj_set_size(ui->device_rgblight_color_btn_1, 32, 32);

	//Write style for device_rgblight_color_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_color_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_color_btn_1, lv_color_hex(0xff00b2), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_color_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_color_btn_1, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_color_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_color_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_color_btn_1, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_color_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_color_btn_2
	ui->device_rgblight_color_btn_2 = lv_btn_create(ui->device_rgblight);
	ui->device_rgblight_color_btn_2_label = lv_label_create(ui->device_rgblight_color_btn_2);
	lv_label_set_text(ui->device_rgblight_color_btn_2_label, "");
	lv_label_set_long_mode(ui->device_rgblight_color_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_rgblight_color_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_rgblight_color_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_rgblight_color_btn_2, 63, 90);
	lv_obj_set_size(ui->device_rgblight_color_btn_2, 32, 32);

	//Write style for device_rgblight_color_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_color_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_color_btn_2, lv_color_hex(0xddff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_color_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_color_btn_2, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_color_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_color_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_color_btn_2, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_color_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_color_btn_3
	ui->device_rgblight_color_btn_3 = lv_btn_create(ui->device_rgblight);
	ui->device_rgblight_color_btn_3_label = lv_label_create(ui->device_rgblight_color_btn_3);
	lv_label_set_text(ui->device_rgblight_color_btn_3_label, "");
	lv_label_set_long_mode(ui->device_rgblight_color_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_rgblight_color_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_rgblight_color_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_rgblight_color_btn_3, 16, 135);
	lv_obj_set_size(ui->device_rgblight_color_btn_3, 32, 32);

	//Write style for device_rgblight_color_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_color_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_color_btn_3, lv_color_hex(0x00fffc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_color_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_color_btn_3, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_color_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_color_btn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_color_btn_3, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_color_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_color_btn_4
	ui->device_rgblight_color_btn_4 = lv_btn_create(ui->device_rgblight);
	ui->device_rgblight_color_btn_4_label = lv_label_create(ui->device_rgblight_color_btn_4);
	lv_label_set_text(ui->device_rgblight_color_btn_4_label, "");
	lv_label_set_long_mode(ui->device_rgblight_color_btn_4_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_rgblight_color_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_rgblight_color_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_rgblight_color_btn_4, 63, 136);
	lv_obj_set_size(ui->device_rgblight_color_btn_4, 32, 32);

	//Write style for device_rgblight_color_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_color_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_color_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_color_btn_4, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_color_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_rgblight_color_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_color_btn_4, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_color_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_color_btn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_color_btn_4, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_color_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_round_color
	ui->device_rgblight_round_color = lv_obj_create(ui->device_rgblight);
	lv_obj_set_pos(ui->device_rgblight_round_color, 175, 71);
	lv_obj_set_size(ui->device_rgblight_round_color, 80, 80);
	lv_obj_set_scrollbar_mode(ui->device_rgblight_round_color, LV_SCROLLBAR_MODE_OFF);

	//Write style for device_rgblight_round_color, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_round_color, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_rgblight_round_color, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_round_color, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_round_color, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_round_color, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_round_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_wc_cpicker
	ui->device_rgblight_wc_cpicker = lv_colorwheel_create(ui->device_rgblight, true);
	lv_obj_set_pos(ui->device_rgblight_wc_cpicker, 140, 36);
	lv_obj_set_size(ui->device_rgblight_wc_cpicker, 150, 150);

	//Write style for device_rgblight_wc_cpicker, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->device_rgblight_wc_cpicker, 20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_brightness_label
	ui->device_rgblight_brightness_label = lv_label_create(ui->device_rgblight);
	lv_label_set_text(ui->device_rgblight_brightness_label, "Brightness");
	lv_label_set_long_mode(ui->device_rgblight_brightness_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_rgblight_brightness_label, 4, 223);
	lv_obj_set_size(ui->device_rgblight_brightness_label, 100, 20);

	//Write style for device_rgblight_brightness_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_brightness_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_brightness_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_brightness_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_brightness_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_brightness_percent_label
	ui->device_rgblight_brightness_percent_label = lv_label_create(ui->device_rgblight);
	lv_label_set_text(ui->device_rgblight_brightness_percent_label, "100%");
	lv_label_set_long_mode(ui->device_rgblight_brightness_percent_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_rgblight_brightness_percent_label, 238, 229);
	lv_obj_set_size(ui->device_rgblight_brightness_percent_label, 55, 20);

	//Write style for device_rgblight_brightness_percent_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_rgblight_brightness_percent_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_rgblight_brightness_percent_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_rgblight_brightness_percent_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_brightness_percent_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_rgblight_brightness_slider
	ui->device_rgblight_brightness_slider = lv_slider_create(ui->device_rgblight);
	lv_slider_set_range(ui->device_rgblight_brightness_slider, 0, 100);
	lv_slider_set_mode(ui->device_rgblight_brightness_slider, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->device_rgblight_brightness_slider, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->device_rgblight_brightness_slider, 25, 249);
	lv_obj_set_size(ui->device_rgblight_brightness_slider, 265, 15);

	//Write style for device_rgblight_brightness_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_brightness_slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_brightness_slider, lv_color_hex(0x434343), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_brightness_slider, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_brightness_slider, lv_color_hex(0x434343), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_brightness_slider, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->device_rgblight_brightness_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_rgblight_brightness_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for device_rgblight_brightness_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_brightness_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_brightness_slider, lv_color_hex(0xcfcfcf), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_brightness_slider, LV_GRAD_DIR_VER, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_brightness_slider, lv_color_hex(0xcfcfcf), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_brightness_slider, 30, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for device_rgblight_brightness_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_rgblight_brightness_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_rgblight_brightness_slider, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_rgblight_brightness_slider, LV_GRAD_DIR_VER, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_rgblight_brightness_slider, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_rgblight_brightness_slider, 30, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->device_rgblight);

	
	//Init events for screen.
	events_init_device_rgblight(ui);
}
