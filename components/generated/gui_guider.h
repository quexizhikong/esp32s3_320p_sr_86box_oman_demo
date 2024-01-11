/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_tileview;
	lv_obj_t *screen_main_tileview_top_drop;
	lv_obj_t *screen_main_tileview_home;
	lv_obj_t *screen_main_tileview_device;
	lv_obj_t *home_screen;
	bool home_screen_del;
	lv_obj_t *home_screen_image_ck_wifi;
	lv_obj_t *home_screen_label_time;
	lv_obj_t *home_screen_label_date;
	lv_obj_t *home_screen_scene_1;
	lv_obj_t *home_screen_returnhome_label;
	lv_obj_t *home_screen_returnhome_imgbtn;
	lv_obj_t *home_screen_returnhome_imgbtn_label;
	lv_obj_t *home_screen_scene_2;
	lv_obj_t *home_screen_awayhome_label;
	lv_obj_t *home_screen_awayhome_imgbtn;
	lv_obj_t *home_screen_awayhome_imgbtn_label;
	lv_obj_t *home_screen_scene_3;
	lv_obj_t *home_screen_love_label;
	lv_obj_t *home_screen_love_imgbtn;
	lv_obj_t *home_screen_love_imgbtn_label;
	lv_obj_t *home_screen_scene_4;
	lv_obj_t *home_screen_audio_label;
	lv_obj_t *home_screen_audio_imgbtn;
	lv_obj_t *home_screen_audio_imgbtn_label;
	lv_obj_t *device_screen;
	bool device_screen_del;
	lv_obj_t *device_screen_device_name_label;
	lv_obj_t *device_screen_dev1_cont;
	lv_obj_t *device_screen_dev1_label;
	lv_obj_t *device_screen_dev1_icon_bg;
	lv_obj_t *device_screen_dev1_icon;
	lv_obj_t *device_screen_dev1_btn;
	lv_obj_t *device_screen_dev1_btn_label;
	lv_obj_t *device_screen_dev2_cont;
	lv_obj_t *device_screen_dev2_label;
	lv_obj_t *device_screen_dev2_icon_bg;
	lv_obj_t *device_screen_dev2_icon;
	lv_obj_t *device_screen_dev2_btn;
	lv_obj_t *device_screen_dev2_btn_label;
	lv_obj_t *device_screen_dev3_cont;
	lv_obj_t *device_screen_dev3_label;
	lv_obj_t *device_screen_dev3_icon_bg;
	lv_obj_t *device_screen_dev3_icon;
	lv_obj_t *device_screen_dev3_btn;
	lv_obj_t *device_screen_dev3_btn_label;
	lv_obj_t *device_screen_dev4_cont;
	lv_obj_t *device_screen_dev4_label;
	lv_obj_t *device_screen_dev4_icon_bg;
	lv_obj_t *device_screen_dev4_icon;
	lv_obj_t *device_screen_dev4_btn;
	lv_obj_t *device_screen_dev4_btn_label;
	lv_obj_t *screen_top_drop;
	bool screen_top_drop_del;
	lv_obj_t *screen_top_drop_network_btn;
	lv_obj_t *screen_top_drop_network_btn_label;
	lv_obj_t *screen_top_drop_label_network;
	lv_obj_t *screen_top_drop_setting_btn;
	lv_obj_t *screen_top_drop_setting_btn_label;
	lv_obj_t *screen_top_drop_label_setting;
	lv_obj_t *screen_top_drop_upgrade_scene_btn;
	lv_obj_t *screen_top_drop_upgrade_scene_btn_label;
	lv_obj_t *screen_top_drop_label_upgrade_scene;
	lv_obj_t *screen_top_drop_soud_con;
	lv_obj_t *screen_top_drop_label_volume;
	lv_obj_t *screen_top_drop_slider_soud;
	lv_obj_t *screen_wificonf;
	bool screen_wificonf_del;
	lv_obj_t *screen_wificonf_returnbg;
	lv_obj_t *screen_wificonf_return_imgbtn;
	lv_obj_t *screen_wificonf_return_imgbtn_label;
	lv_obj_t *screen_wificonf_smartconfig_img;
	lv_obj_t *screen_wificonf_smartconfig_btn;
	lv_obj_t *screen_wificonf_smartconfig_btn_label;
	lv_obj_t *screen_setting;
	bool screen_setting_del;
	lv_obj_t *screen_setting_returnimg;
	lv_obj_t *screen_setting_return_imgbtn;
	lv_obj_t *screen_setting_return_imgbtn_label;
	lv_obj_t *screen_setting_label_set;
	lv_obj_t *screen_setting_list_1;
	lv_obj_t *screen_setting_list_1_item0;
	lv_obj_t *screen_setting_list_1_item1;
	lv_obj_t *screen_setting_list_1_item2;
	lv_obj_t *device_rgblight;
	bool device_rgblight_del;
	lv_obj_t *device_rgblight_return_img;
	lv_obj_t *device_rgblight_return_imgbtn;
	lv_obj_t *device_rgblight_return_imgbtn_label;
	lv_obj_t *device_rgblight_light_sw;
	lv_obj_t *device_rgblight_color_btn_1;
	lv_obj_t *device_rgblight_color_btn_1_label;
	lv_obj_t *device_rgblight_color_btn_2;
	lv_obj_t *device_rgblight_color_btn_2_label;
	lv_obj_t *device_rgblight_color_btn_3;
	lv_obj_t *device_rgblight_color_btn_3_label;
	lv_obj_t *device_rgblight_color_btn_4;
	lv_obj_t *device_rgblight_color_btn_4_label;
	lv_obj_t *device_rgblight_round_color;
	lv_obj_t *device_rgblight_wc_cpicker;
	lv_obj_t *device_rgblight_brightness_label;
	lv_obj_t *device_rgblight_brightness_percent_label;
	lv_obj_t *device_rgblight_brightness_slider;
	lv_obj_t *voiceauto_screen;
	bool voiceauto_screen_del;
	lv_obj_t *voiceauto_screen_animimg_1;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen_main(lv_ui *ui);
void setup_scr_home_screen(lv_ui *ui);
void setup_scr_device_screen(lv_ui *ui);
void setup_scr_screen_top_drop(lv_ui *ui);
void setup_scr_screen_wificonf(lv_ui *ui);
void setup_scr_screen_setting(lv_ui *ui);
void setup_scr_device_rgblight(lv_ui *ui);
void setup_scr_voiceauto_screen(lv_ui *ui);
LV_IMG_DECLARE(_wifisignal0_alpha_20x16);
LV_IMG_DECLARE(_icon_go_home_alpha_32x32);
LV_IMG_DECLARE(_icon_go_home_alpha_32x32);
LV_IMG_DECLARE(_icon_go_home_alpha_32x32);
LV_IMG_DECLARE(_icon_go_home_alpha_32x32);
LV_IMG_DECLARE(_icon_away_alpha_32x32);
LV_IMG_DECLARE(_icon_away_alpha_32x32);
LV_IMG_DECLARE(_icon_away_alpha_32x32);
LV_IMG_DECLARE(_icon_away_alpha_32x32);
LV_IMG_DECLARE(_icon_love_alpha_32x32);
LV_IMG_DECLARE(_icon_love_alpha_32x32);
LV_IMG_DECLARE(_icon_love_alpha_32x32);
LV_IMG_DECLARE(_icon_love_alpha_32x32);
LV_IMG_DECLARE(_icon_movie_alpha_32x32);
LV_IMG_DECLARE(_icon_movie_alpha_32x32);
LV_IMG_DECLARE(_icon_movie_alpha_32x32);
LV_IMG_DECLARE(_icon_movie_alpha_32x32);
LV_IMG_DECLARE(_onofflighton1_alpha_32x32);
LV_IMG_DECLARE(_onofflighton1_alpha_32x32);
LV_IMG_DECLARE(_onofflighton1_alpha_32x32);
LV_IMG_DECLARE(_onofflighton1_alpha_32x32);
LV_IMG_DECLARE(_set_wifi_alpha_50x50);
LV_IMG_DECLARE(_set_wifi_alpha_50x50);
LV_IMG_DECLARE(_set_wifi_alpha_50x50);
LV_IMG_DECLARE(_set_wifi_alpha_50x50);
LV_IMG_DECLARE(_set_seting_alpha_50x50);
LV_IMG_DECLARE(_set_seting_alpha_50x50);
LV_IMG_DECLARE(_set_seting_alpha_50x50);
LV_IMG_DECLARE(_set_seting_alpha_50x50);
LV_IMG_DECLARE(_set_update_alpha_50x50);
LV_IMG_DECLARE(_set_update_alpha_50x50);
LV_IMG_DECLARE(_set_update_alpha_50x50);
LV_IMG_DECLARE(_set_update_alpha_50x50);
LV_IMG_DECLARE(_returnbg_alpha_28x22);
LV_IMG_DECLARE(_smartconfig_icon_alpha_106x127);
LV_IMG_DECLARE(_returnbg_alpha_28x22);
LV_IMG_DECLARE(_returnbg_alpha_28x22);
#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00000);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00001);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00002);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00003);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00004);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00005);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00006);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00007);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00008);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00009);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00010);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00011);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00012);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00013);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00014);
LV_IMG_DECLARE(voiceauto_screen_animimg_1ball_00015);

LV_FONT_DECLARE(lv_font_PingFang_Regular_64)
LV_FONT_DECLARE(lv_font_simsun_64)
LV_FONT_DECLARE(lv_font_PingFang_Regular_16)
LV_FONT_DECLARE(lv_font_simsun_16)
LV_FONT_DECLARE(lv_font_simsun_12)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
