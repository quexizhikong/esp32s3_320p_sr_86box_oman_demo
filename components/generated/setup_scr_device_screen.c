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


void setup_scr_device_screen(lv_ui *ui)
{
	//Write codes device_screen
	//ui->device_screen = lv_obj_create(NULL);
	ui->device_screen = lv_tileview_add_tile(ui->screen_main_tileview, 2, 1, LV_DIR_LEFT);

	//Write style for device_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_device_name_label
	ui->device_screen_device_name_label = lv_label_create(ui->device_screen);
	lv_label_set_text(ui->device_screen_device_name_label, "Device");
	lv_label_set_long_mode(ui->device_screen_device_name_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_device_name_label, 110, 8);
	lv_obj_set_size(ui->device_screen_device_name_label, 100, 20);

	//Write style for device_screen_device_name_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_device_name_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_device_name_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_device_name_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_device_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev1_cont
	ui->device_screen_dev1_cont = lv_obj_create(ui->device_screen);
	lv_obj_set_pos(ui->device_screen_dev1_cont, 10, 38);
	lv_obj_set_size(ui->device_screen_dev1_cont, 145, 110);
	lv_obj_set_scrollbar_mode(ui->device_screen_dev1_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for device_screen_dev1_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev1_cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev1_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev1_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev1_cont, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev1_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev1_label
	ui->device_screen_dev1_label = lv_label_create(ui->device_screen_dev1_cont);
	lv_label_set_text(ui->device_screen_dev1_label, "room 1");
	lv_label_set_long_mode(ui->device_screen_dev1_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev1_label, 0, 66);
	lv_obj_set_size(ui->device_screen_dev1_label, 144, 34);

	//Write style for device_screen_dev1_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev1_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev1_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev1_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev1_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev1_icon_bg
	ui->device_screen_dev1_icon_bg = lv_label_create(ui->device_screen_dev1_cont);
	lv_label_set_text(ui->device_screen_dev1_icon_bg, "");
	lv_label_set_long_mode(ui->device_screen_dev1_icon_bg, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev1_icon_bg, 11, 9);
	lv_obj_set_size(ui->device_screen_dev1_icon_bg, 50, 50);

	//Write style for device_screen_dev1_icon_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev1_icon_bg, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev1_icon_bg, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev1_icon_bg, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev1_icon_bg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev1_icon_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev1_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev1_icon_bg, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev1_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev1_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev1_icon
	ui->device_screen_dev1_icon = lv_img_create(ui->device_screen_dev1_cont);
	lv_obj_add_flag(ui->device_screen_dev1_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->device_screen_dev1_icon, &_onofflighton1_alpha_32x32);
	lv_img_set_pivot(ui->device_screen_dev1_icon, 0,0);
	lv_img_set_angle(ui->device_screen_dev1_icon, 0);
	lv_obj_set_pos(ui->device_screen_dev1_icon, 20, 18);
	lv_obj_set_size(ui->device_screen_dev1_icon, 32, 32);

	//Write style for device_screen_dev1_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->device_screen_dev1_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev1_btn
	ui->device_screen_dev1_btn = lv_btn_create(ui->device_screen_dev1_cont);
	ui->device_screen_dev1_btn_label = lv_label_create(ui->device_screen_dev1_btn);
	lv_label_set_text(ui->device_screen_dev1_btn_label, "");
	lv_label_set_long_mode(ui->device_screen_dev1_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_screen_dev1_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_screen_dev1_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_screen_dev1_btn, 0, 0);
	lv_obj_set_size(ui->device_screen_dev1_btn, 145, 110);

	//Write style for device_screen_dev1_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_screen_dev1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_screen_dev1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev1_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev1_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev1_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev2_cont
	ui->device_screen_dev2_cont = lv_obj_create(ui->device_screen);
	lv_obj_set_pos(ui->device_screen_dev2_cont, 165, 38);
	lv_obj_set_size(ui->device_screen_dev2_cont, 145, 110);
	lv_obj_set_scrollbar_mode(ui->device_screen_dev2_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for device_screen_dev2_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev2_cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev2_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev2_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev2_cont, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev2_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev2_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev2_label
	ui->device_screen_dev2_label = lv_label_create(ui->device_screen_dev2_cont);
	lv_label_set_text(ui->device_screen_dev2_label, "room 2\n");
	lv_label_set_long_mode(ui->device_screen_dev2_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev2_label, 1, 66);
	lv_obj_set_size(ui->device_screen_dev2_label, 144, 34);

	//Write style for device_screen_dev2_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev2_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev2_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev2_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev2_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev2_icon_bg
	ui->device_screen_dev2_icon_bg = lv_label_create(ui->device_screen_dev2_cont);
	lv_label_set_text(ui->device_screen_dev2_icon_bg, "");
	lv_label_set_long_mode(ui->device_screen_dev2_icon_bg, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev2_icon_bg, 11, 9);
	lv_obj_set_size(ui->device_screen_dev2_icon_bg, 50, 50);

	//Write style for device_screen_dev2_icon_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev2_icon_bg, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev2_icon_bg, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev2_icon_bg, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev2_icon_bg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev2_icon_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev2_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev2_icon_bg, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev2_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev2_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev2_icon
	ui->device_screen_dev2_icon = lv_img_create(ui->device_screen_dev2_cont);
	lv_obj_add_flag(ui->device_screen_dev2_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->device_screen_dev2_icon, &_onofflighton1_alpha_32x32);
	lv_img_set_pivot(ui->device_screen_dev2_icon, 0,0);
	lv_img_set_angle(ui->device_screen_dev2_icon, 0);
	lv_obj_set_pos(ui->device_screen_dev2_icon, 20, 18);
	lv_obj_set_size(ui->device_screen_dev2_icon, 32, 32);

	//Write style for device_screen_dev2_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->device_screen_dev2_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev2_btn
	ui->device_screen_dev2_btn = lv_btn_create(ui->device_screen_dev2_cont);
	ui->device_screen_dev2_btn_label = lv_label_create(ui->device_screen_dev2_btn);
	lv_label_set_text(ui->device_screen_dev2_btn_label, "");
	lv_label_set_long_mode(ui->device_screen_dev2_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_screen_dev2_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_screen_dev2_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_screen_dev2_btn, 0, 0);
	lv_obj_set_size(ui->device_screen_dev2_btn, 145, 110);

	//Write style for device_screen_dev2_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_screen_dev2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_screen_dev2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev2_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev2_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev2_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev3_cont
	ui->device_screen_dev3_cont = lv_obj_create(ui->device_screen);
	lv_obj_set_pos(ui->device_screen_dev3_cont, 10, 154);
	lv_obj_set_size(ui->device_screen_dev3_cont, 145, 110);
	lv_obj_set_scrollbar_mode(ui->device_screen_dev3_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for device_screen_dev3_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev3_cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev3_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev3_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev3_cont, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev3_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev3_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev3_label
	ui->device_screen_dev3_label = lv_label_create(ui->device_screen_dev3_cont);
	lv_label_set_text(ui->device_screen_dev3_label, "room 3\n");
	lv_label_set_long_mode(ui->device_screen_dev3_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev3_label, 1, 65);
	lv_obj_set_size(ui->device_screen_dev3_label, 144, 34);

	//Write style for device_screen_dev3_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev3_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev3_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev3_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev3_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev3_icon_bg
	ui->device_screen_dev3_icon_bg = lv_label_create(ui->device_screen_dev3_cont);
	lv_label_set_text(ui->device_screen_dev3_icon_bg, "");
	lv_label_set_long_mode(ui->device_screen_dev3_icon_bg, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev3_icon_bg, 11, 9);
	lv_obj_set_size(ui->device_screen_dev3_icon_bg, 50, 50);

	//Write style for device_screen_dev3_icon_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev3_icon_bg, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev3_icon_bg, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev3_icon_bg, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev3_icon_bg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev3_icon_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev3_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev3_icon_bg, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev3_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev3_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev3_icon
	ui->device_screen_dev3_icon = lv_img_create(ui->device_screen_dev3_cont);
	lv_obj_add_flag(ui->device_screen_dev3_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->device_screen_dev3_icon, &_onofflighton1_alpha_32x32);
	lv_img_set_pivot(ui->device_screen_dev3_icon, 0,0);
	lv_img_set_angle(ui->device_screen_dev3_icon, 0);
	lv_obj_set_pos(ui->device_screen_dev3_icon, 20, 18);
	lv_obj_set_size(ui->device_screen_dev3_icon, 32, 32);

	//Write style for device_screen_dev3_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->device_screen_dev3_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev3_btn
	ui->device_screen_dev3_btn = lv_btn_create(ui->device_screen_dev3_cont);
	ui->device_screen_dev3_btn_label = lv_label_create(ui->device_screen_dev3_btn);
	lv_label_set_text(ui->device_screen_dev3_btn_label, "");
	lv_label_set_long_mode(ui->device_screen_dev3_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_screen_dev3_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_screen_dev3_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_screen_dev3_btn, 0, 0);
	lv_obj_set_size(ui->device_screen_dev3_btn, 145, 110);

	//Write style for device_screen_dev3_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_screen_dev3_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_screen_dev3_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev3_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev3_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev3_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev3_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev3_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev4_cont
	ui->device_screen_dev4_cont = lv_obj_create(ui->device_screen);
	lv_obj_set_pos(ui->device_screen_dev4_cont, 165, 154);
	lv_obj_set_size(ui->device_screen_dev4_cont, 145, 110);
	lv_obj_set_scrollbar_mode(ui->device_screen_dev4_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for device_screen_dev4_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev4_cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev4_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev4_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev4_cont, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev4_cont, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev4_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev4_label
	ui->device_screen_dev4_label = lv_label_create(ui->device_screen_dev4_cont);
	lv_label_set_text(ui->device_screen_dev4_label, "room 4");
	lv_label_set_long_mode(ui->device_screen_dev4_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev4_label, 1, 65);
	lv_obj_set_size(ui->device_screen_dev4_label, 144, 34);

	//Write style for device_screen_dev4_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev4_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev4_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev4_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev4_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev4_icon_bg
	ui->device_screen_dev4_icon_bg = lv_label_create(ui->device_screen_dev4_cont);
	lv_label_set_text(ui->device_screen_dev4_icon_bg, "");
	lv_label_set_long_mode(ui->device_screen_dev4_icon_bg, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->device_screen_dev4_icon_bg, 11, 9);
	lv_obj_set_size(ui->device_screen_dev4_icon_bg, 50, 50);

	//Write style for device_screen_dev4_icon_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev4_icon_bg, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev4_icon_bg, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev4_icon_bg, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev4_icon_bg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->device_screen_dev4_icon_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->device_screen_dev4_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->device_screen_dev4_icon_bg, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->device_screen_dev4_icon_bg, lv_color_hex(0x424242), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev4_icon_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev4_icon
	ui->device_screen_dev4_icon = lv_img_create(ui->device_screen_dev4_cont);
	lv_obj_add_flag(ui->device_screen_dev4_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->device_screen_dev4_icon, &_onofflighton1_alpha_32x32);
	lv_img_set_pivot(ui->device_screen_dev4_icon, 0,0);
	lv_img_set_angle(ui->device_screen_dev4_icon, 0);
	lv_obj_set_pos(ui->device_screen_dev4_icon, 20, 18);
	lv_obj_set_size(ui->device_screen_dev4_icon, 32, 32);

	//Write style for device_screen_dev4_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->device_screen_dev4_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_dev4_btn
	ui->device_screen_dev4_btn = lv_btn_create(ui->device_screen_dev4_cont);
	ui->device_screen_dev4_btn_label = lv_label_create(ui->device_screen_dev4_btn);
	lv_label_set_text(ui->device_screen_dev4_btn_label, "");
	lv_label_set_long_mode(ui->device_screen_dev4_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->device_screen_dev4_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->device_screen_dev4_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->device_screen_dev4_btn, 0, 0);
	lv_obj_set_size(ui->device_screen_dev4_btn, 145, 110);

	//Write style for device_screen_dev4_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->device_screen_dev4_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->device_screen_dev4_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->device_screen_dev4_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->device_screen_dev4_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->device_screen_dev4_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->device_screen_dev4_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->device_screen_dev4_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->device_screen);

	
	//Init events for screen.
	events_init_device_screen(ui);
}
