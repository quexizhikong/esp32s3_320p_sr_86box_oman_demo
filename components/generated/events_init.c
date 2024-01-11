/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void home_screen_returnhome_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void home_screen_awayhome_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void home_screen_love_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void home_screen_audio_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_home_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->home_screen_returnhome_imgbtn, home_screen_returnhome_imgbtn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->home_screen_awayhome_imgbtn, home_screen_awayhome_imgbtn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->home_screen_love_imgbtn, home_screen_love_imgbtn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->home_screen_audio_imgbtn, home_screen_audio_imgbtn_event_handler, LV_EVENT_ALL, NULL);
}
static void device_screen_dev1_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_screen_dev2_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_screen_dev3_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_screen_dev4_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_device_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->device_screen_dev1_btn, device_screen_dev1_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_screen_dev2_btn, device_screen_dev2_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_screen_dev3_btn, device_screen_dev3_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_screen_dev4_btn, device_screen_dev4_btn_event_handler, LV_EVENT_ALL, NULL);
}
static void screen_top_drop_network_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void screen_top_drop_setting_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void screen_top_drop_upgrade_scene_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_PRESSED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void screen_top_drop_slider_soud_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_top_drop(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_top_drop_network_btn, screen_top_drop_network_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_top_drop_setting_btn, screen_top_drop_setting_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_top_drop_upgrade_scene_btn, screen_top_drop_upgrade_scene_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_top_drop_slider_soud, screen_top_drop_slider_soud_event_handler, LV_EVENT_ALL, NULL);
}
static void screen_wificonf_return_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void screen_wificonf_smartconfig_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_RELEASED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_wificonf(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_wificonf_return_imgbtn, screen_wificonf_return_imgbtn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_wificonf_smartconfig_btn, screen_wificonf_smartconfig_btn_event_handler, LV_EVENT_ALL, NULL);
}
static void screen_setting_return_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_screen_setting(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_setting_return_imgbtn, screen_setting_return_imgbtn_event_handler, LV_EVENT_ALL, NULL);
}
static void device_rgblight_return_imgbtn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_light_sw_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_color_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_color_btn_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_color_btn_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_color_btn_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void device_rgblight_brightness_slider_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		
		break;
	}
	default:
		break;
	}
}
void events_init_device_rgblight(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->device_rgblight_return_imgbtn, device_rgblight_return_imgbtn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_light_sw, device_rgblight_light_sw_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_color_btn_1, device_rgblight_color_btn_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_color_btn_2, device_rgblight_color_btn_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_color_btn_3, device_rgblight_color_btn_3_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_color_btn_4, device_rgblight_color_btn_4_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->device_rgblight_brightness_slider, device_rgblight_brightness_slider_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
