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

void screen_main_build(lv_ui *ui)
{
    if(ui->screen_main) return;
    ui->screen_main = lv_obj_create(NULL);

	//Write codes menu
	ui->screen_main_tileview = lv_tileview_create(ui->screen_main);
    lv_obj_remove_style(ui->screen_main_tileview,NULL, LV_PART_SCROLLBAR);

    setup_scr_home_screen(ui);
    setup_scr_screen_top_drop(ui);
    setup_scr_device_screen(ui);
}
void screen_main_show(lv_ui *ui)
{
    if(!ui->screen_main)
    {
        screen_main_build(ui);
    }
    lv_scr_load(ui->screen_main);

    lv_obj_set_tile_id(ui->screen_main_tileview, 1, 1, LV_ANIM_OFF);
}

void screen_main_showdevice(lv_ui *ui)
{
    if(!ui->screen_main)
    {
        screen_main_build(ui);
    }
    lv_scr_load(ui->screen_main);

    lv_obj_set_tile_id(ui->screen_main_tileview, 2, 1, LV_ANIM_OFF);
}

void screen_main_delete(lv_ui *ui)
{
    if(ui->screen_main)
    {
        lv_obj_del(ui->screen_main);
        ui->screen_main = NULL;
    }
}

void setup_scr_screen_main(lv_ui *ui){
	screen_main_build(ui);
	screen_main_show(ui);
}


