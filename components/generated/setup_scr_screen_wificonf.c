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


void setup_scr_screen_wificonf(lv_ui *ui)
{
	//Write codes screen_wificonf
	ui->screen_wificonf = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_wificonf, 320, 320);

	//Write style for screen_wificonf, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wificonf, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wificonf, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wificonf_returnbg
	ui->screen_wificonf_returnbg = lv_img_create(ui->screen_wificonf);
	lv_obj_add_flag(ui->screen_wificonf_returnbg, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_wificonf_returnbg, &_returnbg_alpha_28x22);
	lv_img_set_pivot(ui->screen_wificonf_returnbg, 0,0);
	lv_img_set_angle(ui->screen_wificonf_returnbg, 0);
	lv_obj_set_pos(ui->screen_wificonf_returnbg, 10, 8);
	lv_obj_set_size(ui->screen_wificonf_returnbg, 28, 22);

	//Write style for screen_wificonf_returnbg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_wificonf_returnbg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wificonf_return_imgbtn
	ui->screen_wificonf_return_imgbtn = lv_btn_create(ui->screen_wificonf);
	ui->screen_wificonf_return_imgbtn_label = lv_label_create(ui->screen_wificonf_return_imgbtn);
	lv_label_set_text(ui->screen_wificonf_return_imgbtn_label, "");
	lv_label_set_long_mode(ui->screen_wificonf_return_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wificonf_return_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wificonf_return_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_wificonf_return_imgbtn, 5, 5);
	lv_obj_set_size(ui->screen_wificonf_return_imgbtn, 60, 32);

	//Write style for screen_wificonf_return_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wificonf_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wificonf_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wificonf_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wificonf_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wificonf_return_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wificonf_return_imgbtn, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wificonf_return_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wificonf_smartconfig_img
	ui->screen_wificonf_smartconfig_img = lv_img_create(ui->screen_wificonf);
	lv_obj_add_flag(ui->screen_wificonf_smartconfig_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_wificonf_smartconfig_img, &_smartconfig_icon_alpha_106x127);
	lv_img_set_pivot(ui->screen_wificonf_smartconfig_img, 0,0);
	lv_img_set_angle(ui->screen_wificonf_smartconfig_img, 0);
	lv_obj_set_pos(ui->screen_wificonf_smartconfig_img, 107, 95);
	lv_obj_set_size(ui->screen_wificonf_smartconfig_img, 106, 127);

	//Write style for screen_wificonf_smartconfig_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_wificonf_smartconfig_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wificonf_smartconfig_btn
	ui->screen_wificonf_smartconfig_btn = lv_btn_create(ui->screen_wificonf);
	ui->screen_wificonf_smartconfig_btn_label = lv_label_create(ui->screen_wificonf_smartconfig_btn);
	lv_label_set_text(ui->screen_wificonf_smartconfig_btn_label, "Smartconfig");
	lv_label_set_long_mode(ui->screen_wificonf_smartconfig_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wificonf_smartconfig_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wificonf_smartconfig_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_wificonf_smartconfig_btn, 103, 217);
	lv_obj_set_size(ui->screen_wificonf_smartconfig_btn, 115, 28);

	//Write style for screen_wificonf_smartconfig_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wificonf_smartconfig_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wificonf_smartconfig_btn, lv_color_hex(0xffaa23), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wificonf_smartconfig_btn, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_wificonf_smartconfig_btn, lv_color_hex(0xffaa23), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wificonf_smartconfig_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wificonf_smartconfig_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wificonf_smartconfig_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wificonf_smartconfig_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wificonf_smartconfig_btn, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wificonf_smartconfig_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_wificonf);

	
	//Init events for screen.
	events_init_screen_wificonf(ui);
}
