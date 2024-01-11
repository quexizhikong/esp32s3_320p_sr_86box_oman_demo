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


void setup_scr_screen_top_drop(lv_ui *ui)
{
	//Write codes screen_top_drop
	//ui->screen_top_drop = lv_obj_create(NULL);
	ui->screen_top_drop = lv_tileview_add_tile(ui->screen_main_tileview, 1, 0, LV_DIR_BOTTOM);

	//Write style for screen_top_drop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_top_drop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_top_drop, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_network_btn
	ui->screen_top_drop_network_btn = lv_imgbtn_create(ui->screen_top_drop);
	lv_obj_add_flag(ui->screen_top_drop_network_btn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_top_drop_network_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_set_wifi_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_network_btn, LV_IMGBTN_STATE_PRESSED, NULL, &_set_wifi_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_network_btn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_set_wifi_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_network_btn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_set_wifi_alpha_50x50, NULL);
	ui->screen_top_drop_network_btn_label = lv_label_create(ui->screen_top_drop_network_btn);
	lv_label_set_text(ui->screen_top_drop_network_btn_label, "");
	lv_label_set_long_mode(ui->screen_top_drop_network_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_top_drop_network_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_top_drop_network_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_top_drop_network_btn, 35, 20);
	lv_obj_set_size(ui->screen_top_drop_network_btn, 50, 50);

	//Write style for screen_top_drop_network_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_top_drop_network_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_network_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_network_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_network_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_top_drop_network_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_network_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_top_drop_network_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_top_drop_network_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_network_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_top_drop_network_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_network_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_top_drop_network_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_top_drop_network_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_network_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_top_drop_network_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_network_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_top_drop_label_network
	ui->screen_top_drop_label_network = lv_label_create(ui->screen_top_drop);
	lv_label_set_text(ui->screen_top_drop_label_network, "Network");
	lv_label_set_long_mode(ui->screen_top_drop_label_network, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_top_drop_label_network, 19, 75);
	lv_obj_set_size(ui->screen_top_drop_label_network, 83, 20);

	//Write style for screen_top_drop_label_network, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_top_drop_label_network, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_label_network, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_label_network, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_label_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_setting_btn
	ui->screen_top_drop_setting_btn = lv_imgbtn_create(ui->screen_top_drop);
	lv_obj_add_flag(ui->screen_top_drop_setting_btn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_top_drop_setting_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_set_seting_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_setting_btn, LV_IMGBTN_STATE_PRESSED, NULL, &_set_seting_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_setting_btn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_set_seting_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_setting_btn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_set_seting_alpha_50x50, NULL);
	ui->screen_top_drop_setting_btn_label = lv_label_create(ui->screen_top_drop_setting_btn);
	lv_label_set_text(ui->screen_top_drop_setting_btn_label, "");
	lv_label_set_long_mode(ui->screen_top_drop_setting_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_top_drop_setting_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_top_drop_setting_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_top_drop_setting_btn, 135, 22);
	lv_obj_set_size(ui->screen_top_drop_setting_btn, 50, 50);

	//Write style for screen_top_drop_setting_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_top_drop_setting_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_setting_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_setting_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_setting_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_top_drop_setting_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_setting_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_top_drop_setting_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_top_drop_setting_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_setting_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_top_drop_setting_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_setting_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_top_drop_setting_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_top_drop_setting_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_setting_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_top_drop_setting_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_setting_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_top_drop_label_setting
	ui->screen_top_drop_label_setting = lv_label_create(ui->screen_top_drop);
	lv_label_set_text(ui->screen_top_drop_label_setting, "Settings");
	lv_label_set_long_mode(ui->screen_top_drop_label_setting, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_top_drop_label_setting, 118, 75);
	lv_obj_set_size(ui->screen_top_drop_label_setting, 83, 20);

	//Write style for screen_top_drop_label_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_top_drop_label_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_label_setting, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_label_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_label_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_upgrade_scene_btn
	ui->screen_top_drop_upgrade_scene_btn = lv_imgbtn_create(ui->screen_top_drop);
	lv_obj_add_flag(ui->screen_top_drop_upgrade_scene_btn, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->screen_top_drop_upgrade_scene_btn, LV_IMGBTN_STATE_RELEASED, NULL, &_set_update_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_upgrade_scene_btn, LV_IMGBTN_STATE_PRESSED, NULL, &_set_update_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_upgrade_scene_btn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_set_update_alpha_50x50, NULL);
	lv_imgbtn_set_src(ui->screen_top_drop_upgrade_scene_btn, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_set_update_alpha_50x50, NULL);
	ui->screen_top_drop_upgrade_scene_btn_label = lv_label_create(ui->screen_top_drop_upgrade_scene_btn);
	lv_label_set_text(ui->screen_top_drop_upgrade_scene_btn_label, "");
	lv_label_set_long_mode(ui->screen_top_drop_upgrade_scene_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_top_drop_upgrade_scene_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_top_drop_upgrade_scene_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_top_drop_upgrade_scene_btn, 235, 20);
	lv_obj_set_size(ui->screen_top_drop_upgrade_scene_btn, 50, 50);

	//Write style for screen_top_drop_upgrade_scene_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_top_drop_upgrade_scene_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_upgrade_scene_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_upgrade_scene_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_upgrade_scene_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_top_drop_upgrade_scene_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_upgrade_scene_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_top_drop_upgrade_scene_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_top_drop_upgrade_scene_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_upgrade_scene_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_top_drop_upgrade_scene_btn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_upgrade_scene_btn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_top_drop_upgrade_scene_btn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_top_drop_upgrade_scene_btn, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_upgrade_scene_btn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_top_drop_upgrade_scene_btn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_top_drop_upgrade_scene_btn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_top_drop_label_upgrade_scene
	ui->screen_top_drop_label_upgrade_scene = lv_label_create(ui->screen_top_drop);
	lv_label_set_text(ui->screen_top_drop_label_upgrade_scene, "Refresh\n");
	lv_label_set_long_mode(ui->screen_top_drop_label_upgrade_scene, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_top_drop_label_upgrade_scene, 220, 75);
	lv_obj_set_size(ui->screen_top_drop_label_upgrade_scene, 83, 20);

	//Write style for screen_top_drop_label_upgrade_scene, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_top_drop_label_upgrade_scene, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_label_upgrade_scene, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_label_upgrade_scene, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_label_upgrade_scene, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_soud_con
	ui->screen_top_drop_soud_con = lv_obj_create(ui->screen_top_drop);
	lv_obj_set_pos(ui->screen_top_drop_soud_con, 20, 105);
	lv_obj_set_size(ui->screen_top_drop_soud_con, 280, 70);
	lv_obj_set_scrollbar_mode(ui->screen_top_drop_soud_con, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_top_drop_soud_con, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_soud_con, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_top_drop_soud_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_top_drop_soud_con, lv_color_hex(0xd3d3d3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_top_drop_soud_con, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_top_drop_soud_con, lv_color_hex(0xd3d3d3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_soud_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_label_volume
	ui->screen_top_drop_label_volume = lv_label_create(ui->screen_top_drop_soud_con);
	lv_label_set_text(ui->screen_top_drop_label_volume, "Volume");
	lv_label_set_long_mode(ui->screen_top_drop_label_volume, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_top_drop_label_volume, 90, 14);
	lv_obj_set_size(ui->screen_top_drop_label_volume, 100, 20);

	//Write style for screen_top_drop_label_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_top_drop_label_volume, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_top_drop_label_volume, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_top_drop_label_volume, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_label_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_top_drop_slider_soud
	ui->screen_top_drop_slider_soud = lv_slider_create(ui->screen_top_drop_soud_con);
	lv_slider_set_range(ui->screen_top_drop_slider_soud, 0, 100);
	lv_slider_set_mode(ui->screen_top_drop_slider_soud, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_top_drop_slider_soud, 70, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_top_drop_slider_soud, 15, 46);
	lv_obj_set_size(ui->screen_top_drop_slider_soud, 250, 6);

	//Write style for screen_top_drop_slider_soud, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_top_drop_slider_soud, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_top_drop_slider_soud, lv_color_hex(0x606c80), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_top_drop_slider_soud, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_top_drop_slider_soud, lv_color_hex(0x606c80), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_slider_soud, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_top_drop_slider_soud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_top_drop_slider_soud, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_top_drop_slider_soud, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_top_drop_slider_soud, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_top_drop_slider_soud, lv_color_hex(0xff4c4c), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_top_drop_slider_soud, LV_GRAD_DIR_VER, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_top_drop_slider_soud, lv_color_hex(0xff4c4c), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_slider_soud, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_top_drop_slider_soud, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_top_drop_slider_soud, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_top_drop_slider_soud, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_top_drop_slider_soud, LV_GRAD_DIR_VER, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_top_drop_slider_soud, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_top_drop_slider_soud, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_top_drop);

	
	//Init events for screen.
	events_init_screen_top_drop(ui);
}
