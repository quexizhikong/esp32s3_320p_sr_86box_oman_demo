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


void setup_scr_home_screen(lv_ui *ui)
{
	//Write codes home_screen
	//ui->home_screen = lv_obj_create(NULL);
	ui->home_screen = lv_tileview_add_tile(ui->screen_main_tileview, 1, 1, LV_DIR_TOP|LV_DIR_RIGHT);

	//Write style for home_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->home_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_image_ck_wifi
	ui->home_screen_image_ck_wifi = lv_img_create(ui->home_screen);
	lv_obj_add_flag(ui->home_screen_image_ck_wifi, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->home_screen_image_ck_wifi, &_wifisignal0_alpha_20x16);
	lv_img_set_pivot(ui->home_screen_image_ck_wifi, 0,0);
	lv_img_set_angle(ui->home_screen_image_ck_wifi, 0);
	lv_obj_set_pos(ui->home_screen_image_ck_wifi, 293, 7);
	lv_obj_set_size(ui->home_screen_image_ck_wifi, 20, 16);

	//Write style for home_screen_image_ck_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->home_screen_image_ck_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_label_time
	ui->home_screen_label_time = lv_label_create(ui->home_screen);
	lv_label_set_text(ui->home_screen_label_time, "23:06");
	lv_label_set_long_mode(ui->home_screen_label_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_label_time, 70, 35);
	lv_obj_set_size(ui->home_screen_label_time, 180, 60);

	//Write style for home_screen_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_label_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_label_time, &lv_font_PingFang_Regular_64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_label_date
	ui->home_screen_label_date = lv_label_create(ui->home_screen);
	lv_label_set_text(ui->home_screen_label_date, "Friday, March 12th, 2023");
	lv_label_set_long_mode(ui->home_screen_label_date, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_label_date, 0, 106);
	lv_obj_set_size(ui->home_screen_label_date, 320, 20);

	//Write style for home_screen_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_label_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_label_date, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_scene_1
	ui->home_screen_scene_1 = lv_obj_create(ui->home_screen);
	lv_obj_set_pos(ui->home_screen_scene_1, 9, 138);
	lv_obj_set_size(ui->home_screen_scene_1, 147, 70);
	lv_obj_set_scrollbar_mode(ui->home_screen_scene_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_screen_scene_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_scene_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_scene_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_screen_scene_1, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home_screen_scene_1, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->home_screen_scene_1, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_scene_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_returnhome_label
	ui->home_screen_returnhome_label = lv_label_create(ui->home_screen_scene_1);
	lv_label_set_text(ui->home_screen_returnhome_label, "Home mode");
	lv_label_set_long_mode(ui->home_screen_returnhome_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_returnhome_label, 49, 23);
	lv_obj_set_size(ui->home_screen_returnhome_label, 85, 35);

	//Write style for home_screen_returnhome_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_returnhome_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_returnhome_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_returnhome_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_returnhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_returnhome_imgbtn
	ui->home_screen_returnhome_imgbtn = lv_imgbtn_create(ui->home_screen_scene_1);
	lv_obj_add_flag(ui->home_screen_returnhome_imgbtn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->home_screen_returnhome_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &_icon_go_home_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_returnhome_imgbtn, LV_IMGBTN_STATE_PRESSED, NULL, &_icon_go_home_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_returnhome_imgbtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_icon_go_home_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_returnhome_imgbtn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_icon_go_home_alpha_32x32, NULL);
	ui->home_screen_returnhome_imgbtn_label = lv_label_create(ui->home_screen_returnhome_imgbtn);
	lv_label_set_text(ui->home_screen_returnhome_imgbtn_label, "");
	lv_label_set_long_mode(ui->home_screen_returnhome_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->home_screen_returnhome_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->home_screen_returnhome_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->home_screen_returnhome_imgbtn, 7, 18);
	lv_obj_set_size(ui->home_screen_returnhome_imgbtn, 32, 32);

	//Write style for home_screen_returnhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->home_screen_returnhome_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_returnhome_imgbtn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_returnhome_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_returnhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for home_screen_returnhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->home_screen_returnhome_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->home_screen_returnhome_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->home_screen_returnhome_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->home_screen_returnhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for home_screen_returnhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->home_screen_returnhome_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->home_screen_returnhome_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->home_screen_returnhome_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->home_screen_returnhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for home_screen_returnhome_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->home_screen_returnhome_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes home_screen_scene_2
	ui->home_screen_scene_2 = lv_obj_create(ui->home_screen);
	lv_obj_set_pos(ui->home_screen_scene_2, 163, 138);
	lv_obj_set_size(ui->home_screen_scene_2, 147, 70);
	lv_obj_set_scrollbar_mode(ui->home_screen_scene_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_screen_scene_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_scene_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_scene_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_screen_scene_2, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home_screen_scene_2, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->home_screen_scene_2, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_scene_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_awayhome_label
	ui->home_screen_awayhome_label = lv_label_create(ui->home_screen_scene_2);
	lv_label_set_text(ui->home_screen_awayhome_label, "Away home");
	lv_label_set_long_mode(ui->home_screen_awayhome_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_awayhome_label, 49, 23);
	lv_obj_set_size(ui->home_screen_awayhome_label, 85, 35);

	//Write style for home_screen_awayhome_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_awayhome_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_awayhome_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_awayhome_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_awayhome_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_awayhome_imgbtn
	ui->home_screen_awayhome_imgbtn = lv_imgbtn_create(ui->home_screen_scene_2);
	lv_obj_add_flag(ui->home_screen_awayhome_imgbtn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->home_screen_awayhome_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &_icon_away_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_awayhome_imgbtn, LV_IMGBTN_STATE_PRESSED, NULL, &_icon_away_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_awayhome_imgbtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_icon_away_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_awayhome_imgbtn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_icon_away_alpha_32x32, NULL);
	ui->home_screen_awayhome_imgbtn_label = lv_label_create(ui->home_screen_awayhome_imgbtn);
	lv_label_set_text(ui->home_screen_awayhome_imgbtn_label, "");
	lv_label_set_long_mode(ui->home_screen_awayhome_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->home_screen_awayhome_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->home_screen_awayhome_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->home_screen_awayhome_imgbtn, 7, 18);
	lv_obj_set_size(ui->home_screen_awayhome_imgbtn, 32, 32);

	//Write style for home_screen_awayhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->home_screen_awayhome_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_awayhome_imgbtn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_awayhome_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_awayhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for home_screen_awayhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->home_screen_awayhome_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->home_screen_awayhome_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->home_screen_awayhome_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->home_screen_awayhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for home_screen_awayhome_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->home_screen_awayhome_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->home_screen_awayhome_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->home_screen_awayhome_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->home_screen_awayhome_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for home_screen_awayhome_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->home_screen_awayhome_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes home_screen_scene_3
	ui->home_screen_scene_3 = lv_obj_create(ui->home_screen);
	lv_obj_set_pos(ui->home_screen_scene_3, 9, 224);
	lv_obj_set_size(ui->home_screen_scene_3, 147, 70);
	lv_obj_set_scrollbar_mode(ui->home_screen_scene_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_screen_scene_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_scene_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_scene_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_screen_scene_3, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home_screen_scene_3, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->home_screen_scene_3, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_scene_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_love_label
	ui->home_screen_love_label = lv_label_create(ui->home_screen_scene_3);
	lv_label_set_text(ui->home_screen_love_label, "Romantic mode");
	lv_label_set_long_mode(ui->home_screen_love_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_love_label, 49, 23);
	lv_obj_set_size(ui->home_screen_love_label, 85, 35);

	//Write style for home_screen_love_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_love_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_love_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_love_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_love_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_love_imgbtn
	ui->home_screen_love_imgbtn = lv_imgbtn_create(ui->home_screen_scene_3);
	lv_obj_add_flag(ui->home_screen_love_imgbtn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->home_screen_love_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &_icon_love_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_love_imgbtn, LV_IMGBTN_STATE_PRESSED, NULL, &_icon_love_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_love_imgbtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_icon_love_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_love_imgbtn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_icon_love_alpha_32x32, NULL);
	ui->home_screen_love_imgbtn_label = lv_label_create(ui->home_screen_love_imgbtn);
	lv_label_set_text(ui->home_screen_love_imgbtn_label, "");
	lv_label_set_long_mode(ui->home_screen_love_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->home_screen_love_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->home_screen_love_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->home_screen_love_imgbtn, 7, 18);
	lv_obj_set_size(ui->home_screen_love_imgbtn, 32, 32);

	//Write style for home_screen_love_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->home_screen_love_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_love_imgbtn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_love_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_love_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for home_screen_love_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->home_screen_love_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->home_screen_love_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->home_screen_love_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->home_screen_love_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for home_screen_love_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->home_screen_love_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->home_screen_love_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->home_screen_love_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->home_screen_love_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for home_screen_love_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->home_screen_love_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes home_screen_scene_4
	ui->home_screen_scene_4 = lv_obj_create(ui->home_screen);
	lv_obj_set_pos(ui->home_screen_scene_4, 163, 224);
	lv_obj_set_size(ui->home_screen_scene_4, 147, 70);
	lv_obj_set_scrollbar_mode(ui->home_screen_scene_4, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_screen_scene_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_scene_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_scene_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_screen_scene_4, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home_screen_scene_4, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->home_screen_scene_4, lv_color_hex(0x2c2c2c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_scene_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_audio_label
	ui->home_screen_audio_label = lv_label_create(ui->home_screen_scene_4);
	lv_label_set_text(ui->home_screen_audio_label, "Audiovisual mode\n");
	lv_label_set_long_mode(ui->home_screen_audio_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->home_screen_audio_label, 49, 23);
	lv_obj_set_size(ui->home_screen_audio_label, 85, 35);

	//Write style for home_screen_audio_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_screen_audio_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_audio_label, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_audio_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_audio_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_screen_audio_imgbtn
	ui->home_screen_audio_imgbtn = lv_imgbtn_create(ui->home_screen_scene_4);
	lv_obj_add_flag(ui->home_screen_audio_imgbtn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->home_screen_audio_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &_icon_movie_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_audio_imgbtn, LV_IMGBTN_STATE_PRESSED, NULL, &_icon_movie_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_audio_imgbtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_icon_movie_alpha_32x32, NULL);
	lv_imgbtn_set_src(ui->home_screen_audio_imgbtn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_icon_movie_alpha_32x32, NULL);
	ui->home_screen_audio_imgbtn_label = lv_label_create(ui->home_screen_audio_imgbtn);
	lv_label_set_text(ui->home_screen_audio_imgbtn_label, "");
	lv_label_set_long_mode(ui->home_screen_audio_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->home_screen_audio_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->home_screen_audio_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->home_screen_audio_imgbtn, 7, 18);
	lv_obj_set_size(ui->home_screen_audio_imgbtn, 32, 32);

	//Write style for home_screen_audio_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->home_screen_audio_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_screen_audio_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_screen_audio_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_screen_audio_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for home_screen_audio_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->home_screen_audio_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->home_screen_audio_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->home_screen_audio_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->home_screen_audio_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for home_screen_audio_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->home_screen_audio_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->home_screen_audio_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->home_screen_audio_imgbtn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->home_screen_audio_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for home_screen_audio_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->home_screen_audio_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->home_screen);

	
	//Init events for screen.
	events_init_home_screen(ui);
}
