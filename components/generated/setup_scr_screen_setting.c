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


void setup_scr_screen_setting(lv_ui *ui)
{
	//Write codes screen_setting
	ui->screen_setting = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_setting, 320, 320);

	//Write style for screen_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_setting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_returnimg
	ui->screen_setting_returnimg = lv_img_create(ui->screen_setting);
	lv_obj_add_flag(ui->screen_setting_returnimg, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_setting_returnimg, &_returnbg_alpha_28x22);
	lv_img_set_pivot(ui->screen_setting_returnimg, 0,0);
	lv_img_set_angle(ui->screen_setting_returnimg, 0);
	lv_obj_set_pos(ui->screen_setting_returnimg, 10, 8);
	lv_obj_set_size(ui->screen_setting_returnimg, 28, 22);

	//Write style for screen_setting_returnimg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_setting_returnimg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_return_imgbtn
	ui->screen_setting_return_imgbtn = lv_btn_create(ui->screen_setting);
	ui->screen_setting_return_imgbtn_label = lv_label_create(ui->screen_setting_return_imgbtn);
	lv_label_set_text(ui->screen_setting_return_imgbtn_label, "");
	lv_label_set_long_mode(ui->screen_setting_return_imgbtn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_setting_return_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_setting_return_imgbtn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_setting_return_imgbtn, 5, 5);
	lv_obj_set_size(ui->screen_setting_return_imgbtn, 60, 30);

	//Write style for screen_setting_return_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_setting_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_setting_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_setting_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_setting_return_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_setting_return_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_setting_return_imgbtn, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_setting_return_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_label_set
	ui->screen_setting_label_set = lv_label_create(ui->screen_setting);
	lv_label_set_text(ui->screen_setting_label_set, "Settings\n");
	lv_label_set_long_mode(ui->screen_setting_label_set, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_setting_label_set, 110, 10);
	lv_obj_set_size(ui->screen_setting_label_set, 100, 20);

	//Write style for screen_setting_label_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_setting_label_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_setting_label_set, &lv_font_PingFang_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_setting_label_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_setting_label_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_list_1
	ui->screen_setting_list_1 = lv_list_create(ui->screen_setting);
	ui->screen_setting_list_1_item0 =lv_list_add_text(ui->screen_setting_list_1, "Settings");
	ui->screen_setting_list_1_item1 =lv_list_add_text(ui->screen_setting_list_1, "Diasplay");
	ui->screen_setting_list_1_item2 =lv_list_add_text(ui->screen_setting_list_1, "System restart");
	lv_obj_set_pos(ui->screen_setting_list_1, 0, 40);
	lv_obj_set_size(ui->screen_setting_list_1, 320, 276);
	lv_obj_set_scrollbar_mode(ui->screen_setting_list_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_main_main_default
	static lv_style_t style_screen_setting_list_1_main_main_default;
	ui_init_style(&style_screen_setting_list_1_main_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_main_main_default, 5);
	lv_style_set_bg_opa(&style_screen_setting_list_1_main_main_default, 255);
	lv_style_set_bg_color(&style_screen_setting_list_1_main_main_default, lv_color_hex(0x000000));
	lv_style_set_bg_grad_dir(&style_screen_setting_list_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_grad_color(&style_screen_setting_list_1_main_main_default, lv_color_hex(0x000000));
	lv_style_set_border_width(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_radius(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_setting_list_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_list_1, &style_screen_setting_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_main_scrollbar_default
	static lv_style_t style_screen_setting_list_1_main_scrollbar_default;
	ui_init_style(&style_screen_setting_list_1_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_setting_list_1_main_scrollbar_default, 0);
	lv_style_set_bg_opa(&style_screen_setting_list_1_main_scrollbar_default, 0);
	lv_obj_add_style(ui->screen_setting_list_1, &style_screen_setting_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_extra_btns_main_default
	static lv_style_t style_screen_setting_list_1_extra_btns_main_default;
	ui_init_style(&style_screen_setting_list_1_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_btns_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_btns_main_default, &lv_font_simsun_16);
	lv_style_set_radius(&style_screen_setting_list_1_extra_btns_main_default, 0);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_btns_main_default, 255);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_btns_main_default, lv_color_hex(0x2c2c2c));
	lv_style_set_bg_grad_dir(&style_screen_setting_list_1_extra_btns_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_grad_color(&style_screen_setting_list_1_extra_btns_main_default, lv_color_hex(0x2c2c2c));

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_extra_texts_main_default
	static lv_style_t style_screen_setting_list_1_extra_texts_main_default;
	ui_init_style(&style_screen_setting_list_1_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_texts_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_texts_main_default, &lv_font_montserratMedium_12);
	lv_style_set_radius(&style_screen_setting_list_1_extra_texts_main_default, 3);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_texts_main_default, 255);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_texts_main_default, lv_color_hex(0xffffff));

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_setting);

	
	//Init events for screen.
	events_init_screen_setting(ui);
}
