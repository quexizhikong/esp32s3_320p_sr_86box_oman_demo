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


void setup_scr_voiceauto_screen(lv_ui *ui)
{
	//Write codes voiceauto_screen
	ui->voiceauto_screen = lv_obj_create(lv_layer_top());
	lv_obj_set_pos(ui->voiceauto_screen, 0, 0);
	lv_obj_set_size(ui->voiceauto_screen, 320, 320);
	lv_obj_center(ui->voiceauto_screen);

	lv_obj_set_style_bg_color(ui->voiceauto_screen, lv_color_make(0x00, 0x00, 0x00),LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->voiceauto_screen,255,LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->voiceauto_screen,0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->voiceauto_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->voiceauto_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->voiceauto_screen,0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for voiceauto_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->voiceauto_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->voiceauto_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes voiceauto_screen_animimg_1
	ui->voiceauto_screen_animimg_1 = lv_animimg_create(ui->voiceauto_screen);
	lv_animimg_set_src(ui->voiceauto_screen_animimg_1, (const void **) voiceauto_screen_animimg_1_imgs, 16, false);
	lv_animimg_set_duration(ui->voiceauto_screen_animimg_1, 30*16);
	lv_animimg_set_repeat_count(ui->voiceauto_screen_animimg_1, 100);
	lv_img_set_src(ui->voiceauto_screen_animimg_1, voiceauto_screen_animimg_1_imgs[0]);
	lv_obj_set_pos(ui->voiceauto_screen_animimg_1, 113, 113);
	lv_obj_set_size(ui->voiceauto_screen_animimg_1, 94, 94);
    lv_animimg_start(ui->voiceauto_screen_animimg_1);

	//Update current screen layout.
	lv_obj_update_layout(ui->voiceauto_screen);
   // lv_obj_load(ui->voiceauto_screen);
}
