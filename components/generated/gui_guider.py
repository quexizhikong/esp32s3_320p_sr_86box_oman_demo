# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=320,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(320*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 320
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)



# create screen_main
screen_main = lv.obj()
screen_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_main_default
style_screen_main_main_main_default = lv.style_t()
style_screen_main_main_main_default.init()
style_screen_main_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_main_main_main_default.set_bg_opa(255)

# add style for screen_main
screen_main.add_style(style_screen_main_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_main_tileview
screen_main_tileview = lv.tileview(screen_main)
screen_main_tileview.set_pos(int(0),int(0))
screen_main_tileview.set_size(320,320)
screen_main_tileview.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
screen_main_tileview_Title3 = screen_main_tileview.add_tile(2 , 0, lv.DIR.LEFT)
screen_main_tileview_Title2 = screen_main_tileview.add_tile(1 , 0, lv.DIR.LEFT | lv.DIR.RIGHT)
screen_main_tileview_tile1 = screen_main_tileview.add_tile(0, 0, lv.DIR.RIGHT)
# create style style_screen_main_tileview_main_main_default
style_screen_main_tileview_main_main_default = lv.style_t()
style_screen_main_tileview_main_main_default.init()
style_screen_main_tileview_main_main_default.set_radius(0)
style_screen_main_tileview_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_main_tileview_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_main_tileview_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_main_tileview_main_main_default.set_bg_opa(255)

# add style for screen_main_tileview
screen_main_tileview.add_style(style_screen_main_tileview_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_main_tileview_main_scrollbar_default
style_screen_main_tileview_main_scrollbar_default = lv.style_t()
style_screen_main_tileview_main_scrollbar_default.init()
style_screen_main_tileview_main_scrollbar_default.set_radius(0)
style_screen_main_tileview_main_scrollbar_default.set_bg_color(lv.color_make(0xea,0xef,0xf3))
style_screen_main_tileview_main_scrollbar_default.set_bg_opa(255)

# add style for screen_main_tileview
screen_main_tileview.add_style(style_screen_main_tileview_main_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)


# create home_screen
home_screen = lv.obj()
home_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_home_screen_main_main_default
style_home_screen_main_main_default = lv.style_t()
style_home_screen_main_main_default.init()
style_home_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_home_screen_main_main_default.set_bg_opa(255)

# add style for home_screen
home_screen.add_style(style_home_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_image_ck_wifi
home_screen_image_ck_wifi = lv.img(home_screen)
home_screen_image_ck_wifi.set_pos(int(293),int(7))
home_screen_image_ck_wifi.set_size(20,16)
home_screen_image_ck_wifi.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_image_ck_wifi.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-232662042.png','rb') as f:
        home_screen_image_ck_wifi_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-232662042.png')
    sys.exit()

home_screen_image_ck_wifi_img = lv.img_dsc_t({
  'data_size': len(home_screen_image_ck_wifi_img_data),
  'header': {'always_zero': 0, 'w': 20, 'h': 16, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_image_ck_wifi_img_data
})

home_screen_image_ck_wifi.set_src(home_screen_image_ck_wifi_img)
home_screen_image_ck_wifi.set_pivot(0,0)
home_screen_image_ck_wifi.set_angle(0)
# create style style_home_screen_image_ck_wifi_main_main_default
style_home_screen_image_ck_wifi_main_main_default = lv.style_t()
style_home_screen_image_ck_wifi_main_main_default.init()
style_home_screen_image_ck_wifi_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_home_screen_image_ck_wifi_main_main_default.set_img_recolor_opa(0)
style_home_screen_image_ck_wifi_main_main_default.set_img_opa(255)

# add style for home_screen_image_ck_wifi
home_screen_image_ck_wifi.add_style(style_home_screen_image_ck_wifi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_label_time
home_screen_label_time = lv.label(home_screen)
home_screen_label_time.set_pos(int(70),int(35))
home_screen_label_time.set_size(180,60)
home_screen_label_time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_label_time.set_text("23:06")
home_screen_label_time.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_label_time_main_main_default
style_home_screen_label_time_main_main_default = lv.style_t()
style_home_screen_label_time_main_main_default.init()
style_home_screen_label_time_main_main_default.set_radius(0)
style_home_screen_label_time_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_label_time_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_label_time_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_label_time_main_main_default.set_bg_opa(0)
style_home_screen_label_time_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_label_time_main_main_default.set_text_font(lv.font_PingFang_Regular_64)
except AttributeError:
    try:
        style_home_screen_label_time_main_main_default.set_text_font(lv.font_montserrat_64)
    except AttributeError:
        style_home_screen_label_time_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_label_time_main_main_default.set_text_letter_space(0)
style_home_screen_label_time_main_main_default.set_text_line_space(0)
style_home_screen_label_time_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_label_time_main_main_default.set_pad_left(0)
style_home_screen_label_time_main_main_default.set_pad_right(0)
style_home_screen_label_time_main_main_default.set_pad_top(0)
style_home_screen_label_time_main_main_default.set_pad_bottom(0)

# add style for home_screen_label_time
home_screen_label_time.add_style(style_home_screen_label_time_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_label_date
home_screen_label_date = lv.label(home_screen)
home_screen_label_date.set_pos(int(0),int(106))
home_screen_label_date.set_size(320,20)
home_screen_label_date.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_label_date.set_text("Friday, March 12th, 2023")
home_screen_label_date.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_label_date_main_main_default
style_home_screen_label_date_main_main_default = lv.style_t()
style_home_screen_label_date_main_main_default.init()
style_home_screen_label_date_main_main_default.set_radius(0)
style_home_screen_label_date_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_label_date_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_label_date_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_label_date_main_main_default.set_bg_opa(0)
style_home_screen_label_date_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_label_date_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_label_date_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_label_date_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_label_date_main_main_default.set_text_letter_space(0)
style_home_screen_label_date_main_main_default.set_text_line_space(0)
style_home_screen_label_date_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_label_date_main_main_default.set_pad_left(0)
style_home_screen_label_date_main_main_default.set_pad_right(0)
style_home_screen_label_date_main_main_default.set_pad_top(0)
style_home_screen_label_date_main_main_default.set_pad_bottom(0)

# add style for home_screen_label_date
home_screen_label_date.add_style(style_home_screen_label_date_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_scene_1
home_screen_scene_1 = lv.obj(home_screen)
home_screen_scene_1.set_pos(int(9),int(138))
home_screen_scene_1.set_size(147,70)
home_screen_scene_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create home_screen_returnhome_label
home_screen_returnhome_label = lv.label(home_screen_scene_1)
home_screen_returnhome_label.set_pos(int(49),int(23))
home_screen_returnhome_label.set_size(85,35)
home_screen_returnhome_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_returnhome_label.set_text("Home mode")
home_screen_returnhome_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_returnhome_label_main_main_default
style_home_screen_returnhome_label_main_main_default = lv.style_t()
style_home_screen_returnhome_label_main_main_default.init()
style_home_screen_returnhome_label_main_main_default.set_radius(0)
style_home_screen_returnhome_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_returnhome_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_returnhome_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_returnhome_label_main_main_default.set_bg_opa(0)
style_home_screen_returnhome_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_returnhome_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_returnhome_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_returnhome_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_returnhome_label_main_main_default.set_text_letter_space(0)
style_home_screen_returnhome_label_main_main_default.set_text_line_space(0)
style_home_screen_returnhome_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_returnhome_label_main_main_default.set_pad_left(0)
style_home_screen_returnhome_label_main_main_default.set_pad_right(0)
style_home_screen_returnhome_label_main_main_default.set_pad_top(0)
style_home_screen_returnhome_label_main_main_default.set_pad_bottom(0)

# add style for home_screen_returnhome_label
home_screen_returnhome_label.add_style(style_home_screen_returnhome_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_returnhome_imgbtn
home_screen_returnhome_imgbtn = lv.imgbtn(home_screen_scene_1)
home_screen_returnhome_imgbtn.set_pos(int(7),int(18))
home_screen_returnhome_imgbtn.set_size(32,32)
home_screen_returnhome_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png','rb') as f:
        home_screen_returnhome_imgbtn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png')
    sys.exit()

home_screen_returnhome_imgbtn_imgReleased = lv.img_dsc_t({
  'data_size': len(home_screen_returnhome_imgbtn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_returnhome_imgbtn_imgReleased_data
})
home_screen_returnhome_imgbtn.set_src(lv.imgbtn.STATE.RELEASED, None, home_screen_returnhome_imgbtn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png','rb') as f:
        home_screen_returnhome_imgbtn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png')
    sys.exit()

home_screen_returnhome_imgbtn_imgPressed = lv.img_dsc_t({
  'data_size': len(home_screen_returnhome_imgbtn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_returnhome_imgbtn_imgPressed_data
})
home_screen_returnhome_imgbtn.set_src(lv.imgbtn.STATE.PRESSED, None, home_screen_returnhome_imgbtn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png','rb') as f:
        home_screen_returnhome_imgbtn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png')
    sys.exit()

home_screen_returnhome_imgbtn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(home_screen_returnhome_imgbtn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_returnhome_imgbtn_imgCheckedReleased_data
})
home_screen_returnhome_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, home_screen_returnhome_imgbtn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png','rb') as f:
        home_screen_returnhome_imgbtn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1791092290.png')
    sys.exit()

home_screen_returnhome_imgbtn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(home_screen_returnhome_imgbtn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_returnhome_imgbtn_imgCheckedPressed_data
})
home_screen_returnhome_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, home_screen_returnhome_imgbtn_imgCheckedPressed, None)

home_screen_returnhome_imgbtn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_home_screen_returnhome_imgbtn_main_main_default
style_home_screen_returnhome_imgbtn_main_main_default = lv.style_t()
style_home_screen_returnhome_imgbtn_main_main_default.init()
style_home_screen_returnhome_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_home_screen_returnhome_imgbtn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_returnhome_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_returnhome_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_returnhome_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_returnhome_imgbtn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_home_screen_returnhome_imgbtn_main_main_default.set_img_recolor_opa(0)
style_home_screen_returnhome_imgbtn_main_main_default.set_img_opa(255)

# add style for home_screen_returnhome_imgbtn
home_screen_returnhome_imgbtn.add_style(style_home_screen_returnhome_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_home_screen_returnhome_imgbtn_main_main_pressed
style_home_screen_returnhome_imgbtn_main_main_pressed = lv.style_t()
style_home_screen_returnhome_imgbtn_main_main_pressed.init()
style_home_screen_returnhome_imgbtn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_returnhome_imgbtn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_returnhome_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_returnhome_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_home_screen_returnhome_imgbtn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_returnhome_imgbtn_main_main_pressed.set_img_recolor_opa(0)
style_home_screen_returnhome_imgbtn_main_main_pressed.set_img_opa(255)

# add style for home_screen_returnhome_imgbtn
home_screen_returnhome_imgbtn.add_style(style_home_screen_returnhome_imgbtn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_home_screen_returnhome_imgbtn_main_main_checked
style_home_screen_returnhome_imgbtn_main_main_checked = lv.style_t()
style_home_screen_returnhome_imgbtn_main_main_checked.init()
style_home_screen_returnhome_imgbtn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_returnhome_imgbtn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_returnhome_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_returnhome_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_home_screen_returnhome_imgbtn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_returnhome_imgbtn_main_main_checked.set_img_recolor_opa(0)
style_home_screen_returnhome_imgbtn_main_main_checked.set_img_opa(255)

# add style for home_screen_returnhome_imgbtn
home_screen_returnhome_imgbtn.add_style(style_home_screen_returnhome_imgbtn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

# create style style_home_screen_scene_1_main_main_default
style_home_screen_scene_1_main_main_default = lv.style_t()
style_home_screen_scene_1_main_main_default.init()
style_home_screen_scene_1_main_main_default.set_radius(10)
style_home_screen_scene_1_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_1_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_scene_1_main_main_default.set_bg_opa(255)
style_home_screen_scene_1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_scene_1_main_main_default.set_border_width(0)
style_home_screen_scene_1_main_main_default.set_border_opa(0)
style_home_screen_scene_1_main_main_default.set_pad_left(0)
style_home_screen_scene_1_main_main_default.set_pad_right(0)
style_home_screen_scene_1_main_main_default.set_pad_top(0)
style_home_screen_scene_1_main_main_default.set_pad_bottom(0)

# add style for home_screen_scene_1
home_screen_scene_1.add_style(style_home_screen_scene_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_scene_2
home_screen_scene_2 = lv.obj(home_screen)
home_screen_scene_2.set_pos(int(163),int(138))
home_screen_scene_2.set_size(147,70)
home_screen_scene_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create home_screen_awayhome_label
home_screen_awayhome_label = lv.label(home_screen_scene_2)
home_screen_awayhome_label.set_pos(int(49),int(23))
home_screen_awayhome_label.set_size(85,35)
home_screen_awayhome_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_awayhome_label.set_text("Away home")
home_screen_awayhome_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_awayhome_label_main_main_default
style_home_screen_awayhome_label_main_main_default = lv.style_t()
style_home_screen_awayhome_label_main_main_default.init()
style_home_screen_awayhome_label_main_main_default.set_radius(0)
style_home_screen_awayhome_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_awayhome_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_awayhome_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_awayhome_label_main_main_default.set_bg_opa(0)
style_home_screen_awayhome_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_awayhome_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_awayhome_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_awayhome_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_awayhome_label_main_main_default.set_text_letter_space(0)
style_home_screen_awayhome_label_main_main_default.set_text_line_space(0)
style_home_screen_awayhome_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_awayhome_label_main_main_default.set_pad_left(0)
style_home_screen_awayhome_label_main_main_default.set_pad_right(0)
style_home_screen_awayhome_label_main_main_default.set_pad_top(0)
style_home_screen_awayhome_label_main_main_default.set_pad_bottom(0)

# add style for home_screen_awayhome_label
home_screen_awayhome_label.add_style(style_home_screen_awayhome_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_awayhome_imgbtn
home_screen_awayhome_imgbtn = lv.imgbtn(home_screen_scene_2)
home_screen_awayhome_imgbtn.set_pos(int(7),int(18))
home_screen_awayhome_imgbtn.set_size(32,32)
home_screen_awayhome_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png','rb') as f:
        home_screen_awayhome_imgbtn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png')
    sys.exit()

home_screen_awayhome_imgbtn_imgReleased = lv.img_dsc_t({
  'data_size': len(home_screen_awayhome_imgbtn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_awayhome_imgbtn_imgReleased_data
})
home_screen_awayhome_imgbtn.set_src(lv.imgbtn.STATE.RELEASED, None, home_screen_awayhome_imgbtn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png','rb') as f:
        home_screen_awayhome_imgbtn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png')
    sys.exit()

home_screen_awayhome_imgbtn_imgPressed = lv.img_dsc_t({
  'data_size': len(home_screen_awayhome_imgbtn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_awayhome_imgbtn_imgPressed_data
})
home_screen_awayhome_imgbtn.set_src(lv.imgbtn.STATE.PRESSED, None, home_screen_awayhome_imgbtn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png','rb') as f:
        home_screen_awayhome_imgbtn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png')
    sys.exit()

home_screen_awayhome_imgbtn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(home_screen_awayhome_imgbtn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_awayhome_imgbtn_imgCheckedReleased_data
})
home_screen_awayhome_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, home_screen_awayhome_imgbtn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png','rb') as f:
        home_screen_awayhome_imgbtn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1403167710.png')
    sys.exit()

home_screen_awayhome_imgbtn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(home_screen_awayhome_imgbtn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_awayhome_imgbtn_imgCheckedPressed_data
})
home_screen_awayhome_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, home_screen_awayhome_imgbtn_imgCheckedPressed, None)

home_screen_awayhome_imgbtn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_home_screen_awayhome_imgbtn_main_main_default
style_home_screen_awayhome_imgbtn_main_main_default = lv.style_t()
style_home_screen_awayhome_imgbtn_main_main_default.init()
style_home_screen_awayhome_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_home_screen_awayhome_imgbtn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_awayhome_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_awayhome_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_awayhome_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_awayhome_imgbtn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_home_screen_awayhome_imgbtn_main_main_default.set_img_recolor_opa(0)
style_home_screen_awayhome_imgbtn_main_main_default.set_img_opa(255)

# add style for home_screen_awayhome_imgbtn
home_screen_awayhome_imgbtn.add_style(style_home_screen_awayhome_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_home_screen_awayhome_imgbtn_main_main_pressed
style_home_screen_awayhome_imgbtn_main_main_pressed = lv.style_t()
style_home_screen_awayhome_imgbtn_main_main_pressed.init()
style_home_screen_awayhome_imgbtn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_awayhome_imgbtn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_awayhome_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_awayhome_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_home_screen_awayhome_imgbtn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_awayhome_imgbtn_main_main_pressed.set_img_recolor_opa(0)
style_home_screen_awayhome_imgbtn_main_main_pressed.set_img_opa(255)

# add style for home_screen_awayhome_imgbtn
home_screen_awayhome_imgbtn.add_style(style_home_screen_awayhome_imgbtn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_home_screen_awayhome_imgbtn_main_main_checked
style_home_screen_awayhome_imgbtn_main_main_checked = lv.style_t()
style_home_screen_awayhome_imgbtn_main_main_checked.init()
style_home_screen_awayhome_imgbtn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_awayhome_imgbtn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_awayhome_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_awayhome_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_home_screen_awayhome_imgbtn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_awayhome_imgbtn_main_main_checked.set_img_recolor_opa(0)
style_home_screen_awayhome_imgbtn_main_main_checked.set_img_opa(255)

# add style for home_screen_awayhome_imgbtn
home_screen_awayhome_imgbtn.add_style(style_home_screen_awayhome_imgbtn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

# create style style_home_screen_scene_2_main_main_default
style_home_screen_scene_2_main_main_default = lv.style_t()
style_home_screen_scene_2_main_main_default.init()
style_home_screen_scene_2_main_main_default.set_radius(10)
style_home_screen_scene_2_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_2_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_scene_2_main_main_default.set_bg_opa(255)
style_home_screen_scene_2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_scene_2_main_main_default.set_border_width(0)
style_home_screen_scene_2_main_main_default.set_border_opa(0)
style_home_screen_scene_2_main_main_default.set_pad_left(0)
style_home_screen_scene_2_main_main_default.set_pad_right(0)
style_home_screen_scene_2_main_main_default.set_pad_top(0)
style_home_screen_scene_2_main_main_default.set_pad_bottom(0)

# add style for home_screen_scene_2
home_screen_scene_2.add_style(style_home_screen_scene_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_scene_3
home_screen_scene_3 = lv.obj(home_screen)
home_screen_scene_3.set_pos(int(9),int(224))
home_screen_scene_3.set_size(147,70)
home_screen_scene_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create home_screen_love_label
home_screen_love_label = lv.label(home_screen_scene_3)
home_screen_love_label.set_pos(int(49),int(23))
home_screen_love_label.set_size(85,35)
home_screen_love_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_love_label.set_text("Romantic mode")
home_screen_love_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_love_label_main_main_default
style_home_screen_love_label_main_main_default = lv.style_t()
style_home_screen_love_label_main_main_default.init()
style_home_screen_love_label_main_main_default.set_radius(0)
style_home_screen_love_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_love_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_love_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_love_label_main_main_default.set_bg_opa(0)
style_home_screen_love_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_love_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_love_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_love_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_love_label_main_main_default.set_text_letter_space(0)
style_home_screen_love_label_main_main_default.set_text_line_space(0)
style_home_screen_love_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_love_label_main_main_default.set_pad_left(0)
style_home_screen_love_label_main_main_default.set_pad_right(0)
style_home_screen_love_label_main_main_default.set_pad_top(0)
style_home_screen_love_label_main_main_default.set_pad_bottom(0)

# add style for home_screen_love_label
home_screen_love_label.add_style(style_home_screen_love_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_love_imgbtn
home_screen_love_imgbtn = lv.imgbtn(home_screen_scene_3)
home_screen_love_imgbtn.set_pos(int(7),int(18))
home_screen_love_imgbtn.set_size(32,32)
home_screen_love_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png','rb') as f:
        home_screen_love_imgbtn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png')
    sys.exit()

home_screen_love_imgbtn_imgReleased = lv.img_dsc_t({
  'data_size': len(home_screen_love_imgbtn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_love_imgbtn_imgReleased_data
})
home_screen_love_imgbtn.set_src(lv.imgbtn.STATE.RELEASED, None, home_screen_love_imgbtn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png','rb') as f:
        home_screen_love_imgbtn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png')
    sys.exit()

home_screen_love_imgbtn_imgPressed = lv.img_dsc_t({
  'data_size': len(home_screen_love_imgbtn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_love_imgbtn_imgPressed_data
})
home_screen_love_imgbtn.set_src(lv.imgbtn.STATE.PRESSED, None, home_screen_love_imgbtn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png','rb') as f:
        home_screen_love_imgbtn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png')
    sys.exit()

home_screen_love_imgbtn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(home_screen_love_imgbtn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_love_imgbtn_imgCheckedReleased_data
})
home_screen_love_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, home_screen_love_imgbtn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png','rb') as f:
        home_screen_love_imgbtn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp232649894.png')
    sys.exit()

home_screen_love_imgbtn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(home_screen_love_imgbtn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_love_imgbtn_imgCheckedPressed_data
})
home_screen_love_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, home_screen_love_imgbtn_imgCheckedPressed, None)

home_screen_love_imgbtn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_home_screen_love_imgbtn_main_main_default
style_home_screen_love_imgbtn_main_main_default = lv.style_t()
style_home_screen_love_imgbtn_main_main_default.init()
style_home_screen_love_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_home_screen_love_imgbtn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_love_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_love_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_love_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_love_imgbtn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_home_screen_love_imgbtn_main_main_default.set_img_recolor_opa(0)
style_home_screen_love_imgbtn_main_main_default.set_img_opa(255)

# add style for home_screen_love_imgbtn
home_screen_love_imgbtn.add_style(style_home_screen_love_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_home_screen_love_imgbtn_main_main_pressed
style_home_screen_love_imgbtn_main_main_pressed = lv.style_t()
style_home_screen_love_imgbtn_main_main_pressed.init()
style_home_screen_love_imgbtn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_love_imgbtn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_love_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_love_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_home_screen_love_imgbtn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_love_imgbtn_main_main_pressed.set_img_recolor_opa(0)
style_home_screen_love_imgbtn_main_main_pressed.set_img_opa(255)

# add style for home_screen_love_imgbtn
home_screen_love_imgbtn.add_style(style_home_screen_love_imgbtn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_home_screen_love_imgbtn_main_main_checked
style_home_screen_love_imgbtn_main_main_checked = lv.style_t()
style_home_screen_love_imgbtn_main_main_checked.init()
style_home_screen_love_imgbtn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_love_imgbtn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_love_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_love_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_home_screen_love_imgbtn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_love_imgbtn_main_main_checked.set_img_recolor_opa(0)
style_home_screen_love_imgbtn_main_main_checked.set_img_opa(255)

# add style for home_screen_love_imgbtn
home_screen_love_imgbtn.add_style(style_home_screen_love_imgbtn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

# create style style_home_screen_scene_3_main_main_default
style_home_screen_scene_3_main_main_default = lv.style_t()
style_home_screen_scene_3_main_main_default.init()
style_home_screen_scene_3_main_main_default.set_radius(10)
style_home_screen_scene_3_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_3_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_scene_3_main_main_default.set_bg_opa(255)
style_home_screen_scene_3_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_scene_3_main_main_default.set_border_width(0)
style_home_screen_scene_3_main_main_default.set_border_opa(0)
style_home_screen_scene_3_main_main_default.set_pad_left(0)
style_home_screen_scene_3_main_main_default.set_pad_right(0)
style_home_screen_scene_3_main_main_default.set_pad_top(0)
style_home_screen_scene_3_main_main_default.set_pad_bottom(0)

# add style for home_screen_scene_3
home_screen_scene_3.add_style(style_home_screen_scene_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_scene_4
home_screen_scene_4 = lv.obj(home_screen)
home_screen_scene_4.set_pos(int(163),int(224))
home_screen_scene_4.set_size(147,70)
home_screen_scene_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create home_screen_audio_label
home_screen_audio_label = lv.label(home_screen_scene_4)
home_screen_audio_label.set_pos(int(49),int(23))
home_screen_audio_label.set_size(85,35)
home_screen_audio_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
home_screen_audio_label.set_text("Audiovisual mode\n")
home_screen_audio_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_home_screen_audio_label_main_main_default
style_home_screen_audio_label_main_main_default = lv.style_t()
style_home_screen_audio_label_main_main_default.init()
style_home_screen_audio_label_main_main_default.set_radius(0)
style_home_screen_audio_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_audio_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_audio_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_audio_label_main_main_default.set_bg_opa(0)
style_home_screen_audio_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_home_screen_audio_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_home_screen_audio_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_audio_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_audio_label_main_main_default.set_text_letter_space(0)
style_home_screen_audio_label_main_main_default.set_text_line_space(0)
style_home_screen_audio_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_audio_label_main_main_default.set_pad_left(0)
style_home_screen_audio_label_main_main_default.set_pad_right(0)
style_home_screen_audio_label_main_main_default.set_pad_top(0)
style_home_screen_audio_label_main_main_default.set_pad_bottom(0)

# add style for home_screen_audio_label
home_screen_audio_label.add_style(style_home_screen_audio_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create home_screen_audio_imgbtn
home_screen_audio_imgbtn = lv.imgbtn(home_screen_scene_4)
home_screen_audio_imgbtn.set_pos(int(7),int(18))
home_screen_audio_imgbtn.set_size(32,32)
home_screen_audio_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png','rb') as f:
        home_screen_audio_imgbtn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png')
    sys.exit()

home_screen_audio_imgbtn_imgReleased = lv.img_dsc_t({
  'data_size': len(home_screen_audio_imgbtn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_audio_imgbtn_imgReleased_data
})
home_screen_audio_imgbtn.set_src(lv.imgbtn.STATE.RELEASED, None, home_screen_audio_imgbtn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png','rb') as f:
        home_screen_audio_imgbtn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png')
    sys.exit()

home_screen_audio_imgbtn_imgPressed = lv.img_dsc_t({
  'data_size': len(home_screen_audio_imgbtn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_audio_imgbtn_imgPressed_data
})
home_screen_audio_imgbtn.set_src(lv.imgbtn.STATE.PRESSED, None, home_screen_audio_imgbtn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png','rb') as f:
        home_screen_audio_imgbtn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png')
    sys.exit()

home_screen_audio_imgbtn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(home_screen_audio_imgbtn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_audio_imgbtn_imgCheckedReleased_data
})
home_screen_audio_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, home_screen_audio_imgbtn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png','rb') as f:
        home_screen_audio_imgbtn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp1735511960.png')
    sys.exit()

home_screen_audio_imgbtn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(home_screen_audio_imgbtn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': home_screen_audio_imgbtn_imgCheckedPressed_data
})
home_screen_audio_imgbtn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, home_screen_audio_imgbtn_imgCheckedPressed, None)

home_screen_audio_imgbtn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_home_screen_audio_imgbtn_main_main_default
style_home_screen_audio_imgbtn_main_main_default = lv.style_t()
style_home_screen_audio_imgbtn_main_main_default.init()
style_home_screen_audio_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_home_screen_audio_imgbtn_main_main_default.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_audio_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_audio_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_home_screen_audio_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_home_screen_audio_imgbtn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_home_screen_audio_imgbtn_main_main_default.set_img_recolor_opa(0)
style_home_screen_audio_imgbtn_main_main_default.set_img_opa(255)

# add style for home_screen_audio_imgbtn
home_screen_audio_imgbtn.add_style(style_home_screen_audio_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_home_screen_audio_imgbtn_main_main_pressed
style_home_screen_audio_imgbtn_main_main_pressed = lv.style_t()
style_home_screen_audio_imgbtn_main_main_pressed.init()
style_home_screen_audio_imgbtn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_audio_imgbtn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_audio_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_audio_imgbtn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_home_screen_audio_imgbtn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_audio_imgbtn_main_main_pressed.set_img_recolor_opa(0)
style_home_screen_audio_imgbtn_main_main_pressed.set_img_opa(255)

# add style for home_screen_audio_imgbtn
home_screen_audio_imgbtn.add_style(style_home_screen_audio_imgbtn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_home_screen_audio_imgbtn_main_main_checked
style_home_screen_audio_imgbtn_main_main_checked = lv.style_t()
style_home_screen_audio_imgbtn_main_main_checked.init()
style_home_screen_audio_imgbtn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_home_screen_audio_imgbtn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_home_screen_audio_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_home_screen_audio_imgbtn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_home_screen_audio_imgbtn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_home_screen_audio_imgbtn_main_main_checked.set_img_recolor_opa(0)
style_home_screen_audio_imgbtn_main_main_checked.set_img_opa(255)

# add style for home_screen_audio_imgbtn
home_screen_audio_imgbtn.add_style(style_home_screen_audio_imgbtn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)

# create style style_home_screen_scene_4_main_main_default
style_home_screen_scene_4_main_main_default = lv.style_t()
style_home_screen_scene_4_main_main_default.init()
style_home_screen_scene_4_main_main_default.set_radius(10)
style_home_screen_scene_4_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_4_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_home_screen_scene_4_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_home_screen_scene_4_main_main_default.set_bg_opa(255)
style_home_screen_scene_4_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_home_screen_scene_4_main_main_default.set_border_width(0)
style_home_screen_scene_4_main_main_default.set_border_opa(0)
style_home_screen_scene_4_main_main_default.set_pad_left(0)
style_home_screen_scene_4_main_main_default.set_pad_right(0)
style_home_screen_scene_4_main_main_default.set_pad_top(0)
style_home_screen_scene_4_main_main_default.set_pad_bottom(0)

# add style for home_screen_scene_4
home_screen_scene_4.add_style(style_home_screen_scene_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen
device_screen = lv.obj()
device_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_main_main_default
style_device_screen_main_main_default = lv.style_t()
style_device_screen_main_main_default.init()
style_device_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_device_screen_main_main_default.set_bg_opa(255)

# add style for device_screen
device_screen.add_style(style_device_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_device_name_label
device_screen_device_name_label = lv.label(device_screen)
device_screen_device_name_label.set_pos(int(110),int(8))
device_screen_device_name_label.set_size(100,20)
device_screen_device_name_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_device_name_label.set_text("Device")
device_screen_device_name_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_device_name_label_main_main_default
style_device_screen_device_name_label_main_main_default = lv.style_t()
style_device_screen_device_name_label_main_main_default.init()
style_device_screen_device_name_label_main_main_default.set_radius(0)
style_device_screen_device_name_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_device_name_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_device_name_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_device_name_label_main_main_default.set_bg_opa(0)
style_device_screen_device_name_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_screen_device_name_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_device_name_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_device_name_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_device_name_label_main_main_default.set_text_letter_space(0)
style_device_screen_device_name_label_main_main_default.set_text_line_space(0)
style_device_screen_device_name_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_device_name_label_main_main_default.set_pad_left(0)
style_device_screen_device_name_label_main_main_default.set_pad_right(0)
style_device_screen_device_name_label_main_main_default.set_pad_top(0)
style_device_screen_device_name_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_device_name_label
device_screen_device_name_label.add_style(style_device_screen_device_name_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev1_cont
device_screen_dev1_cont = lv.obj(device_screen)
device_screen_dev1_cont.set_pos(int(10),int(38))
device_screen_dev1_cont.set_size(145,110)
device_screen_dev1_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create device_screen_dev1_label
device_screen_dev1_label = lv.label(device_screen_dev1_cont)
device_screen_dev1_label.set_pos(int(0),int(66))
device_screen_dev1_label.set_size(144,34)
device_screen_dev1_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev1_label.set_text("room 1")
device_screen_dev1_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_dev1_label_main_main_default
style_device_screen_dev1_label_main_main_default = lv.style_t()
style_device_screen_dev1_label_main_main_default.init()
style_device_screen_dev1_label_main_main_default.set_radius(0)
style_device_screen_dev1_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev1_label_main_main_default.set_bg_opa(0)
style_device_screen_dev1_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_screen_dev1_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev1_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev1_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev1_label_main_main_default.set_text_letter_space(0)
style_device_screen_dev1_label_main_main_default.set_text_line_space(0)
style_device_screen_dev1_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev1_label_main_main_default.set_pad_left(0)
style_device_screen_dev1_label_main_main_default.set_pad_right(0)
style_device_screen_dev1_label_main_main_default.set_pad_top(0)
style_device_screen_dev1_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev1_label
device_screen_dev1_label.add_style(style_device_screen_dev1_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev1_icon_bg
device_screen_dev1_icon_bg = lv.label(device_screen_dev1_cont)
device_screen_dev1_icon_bg.set_pos(int(11),int(9))
device_screen_dev1_icon_bg.set_size(50,50)
device_screen_dev1_icon_bg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev1_icon_bg_main_main_default
style_device_screen_dev1_icon_bg_main_main_default = lv.style_t()
style_device_screen_dev1_icon_bg_main_main_default.init()
style_device_screen_dev1_icon_bg_main_main_default.set_radius(10)
style_device_screen_dev1_icon_bg_main_main_default.set_bg_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev1_icon_bg_main_main_default.set_bg_grad_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev1_icon_bg_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev1_icon_bg_main_main_default.set_bg_opa(255)
style_device_screen_dev1_icon_bg_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev1_icon_bg_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev1_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev1_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev1_icon_bg_main_main_default.set_text_letter_space(0)
style_device_screen_dev1_icon_bg_main_main_default.set_text_line_space(0)
style_device_screen_dev1_icon_bg_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev1_icon_bg_main_main_default.set_pad_left(0)
style_device_screen_dev1_icon_bg_main_main_default.set_pad_right(0)
style_device_screen_dev1_icon_bg_main_main_default.set_pad_top(0)
style_device_screen_dev1_icon_bg_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev1_icon_bg
device_screen_dev1_icon_bg.add_style(style_device_screen_dev1_icon_bg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev1_icon
device_screen_dev1_icon = lv.img(device_screen_dev1_cont)
device_screen_dev1_icon.set_pos(int(20),int(18))
device_screen_dev1_icon.set_size(32,32)
device_screen_dev1_icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev1_icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png','rb') as f:
        device_screen_dev1_icon_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png')
    sys.exit()

device_screen_dev1_icon_img = lv.img_dsc_t({
  'data_size': len(device_screen_dev1_icon_img_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': device_screen_dev1_icon_img_data
})

device_screen_dev1_icon.set_src(device_screen_dev1_icon_img)
device_screen_dev1_icon.set_pivot(0,0)
device_screen_dev1_icon.set_angle(0)
# create style style_device_screen_dev1_icon_main_main_default
style_device_screen_dev1_icon_main_main_default = lv.style_t()
style_device_screen_dev1_icon_main_main_default.init()
style_device_screen_dev1_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_device_screen_dev1_icon_main_main_default.set_img_recolor_opa(0)
style_device_screen_dev1_icon_main_main_default.set_img_opa(255)

# add style for device_screen_dev1_icon
device_screen_dev1_icon.add_style(style_device_screen_dev1_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev1_btn
device_screen_dev1_btn = lv.btn(device_screen_dev1_cont)
device_screen_dev1_btn.set_pos(int(0),int(0))
device_screen_dev1_btn.set_size(145,110)
device_screen_dev1_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev1_btn_main_main_default
style_device_screen_dev1_btn_main_main_default = lv.style_t()
style_device_screen_dev1_btn_main_main_default.init()
style_device_screen_dev1_btn_main_main_default.set_radius(0)
style_device_screen_dev1_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev1_btn_main_main_default.set_bg_opa(0)
style_device_screen_dev1_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_btn_main_main_default.set_border_width(0)
style_device_screen_dev1_btn_main_main_default.set_border_opa(255)
style_device_screen_dev1_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev1_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev1_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev1_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev1_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_dev1_btn
device_screen_dev1_btn.add_style(style_device_screen_dev1_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_dev1_cont_main_main_default
style_device_screen_dev1_cont_main_main_default = lv.style_t()
style_device_screen_dev1_cont_main_main_default.init()
style_device_screen_dev1_cont_main_main_default.set_radius(10)
style_device_screen_dev1_cont_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev1_cont_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev1_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev1_cont_main_main_default.set_bg_opa(255)
style_device_screen_dev1_cont_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev1_cont_main_main_default.set_border_width(0)
style_device_screen_dev1_cont_main_main_default.set_border_opa(0)
style_device_screen_dev1_cont_main_main_default.set_pad_left(0)
style_device_screen_dev1_cont_main_main_default.set_pad_right(0)
style_device_screen_dev1_cont_main_main_default.set_pad_top(0)
style_device_screen_dev1_cont_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev1_cont
device_screen_dev1_cont.add_style(style_device_screen_dev1_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev2_cont
device_screen_dev2_cont = lv.obj(device_screen)
device_screen_dev2_cont.set_pos(int(165),int(38))
device_screen_dev2_cont.set_size(145,110)
device_screen_dev2_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create device_screen_dev2_label
device_screen_dev2_label = lv.label(device_screen_dev2_cont)
device_screen_dev2_label.set_pos(int(1),int(66))
device_screen_dev2_label.set_size(144,34)
device_screen_dev2_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev2_label.set_text("room 2\n")
device_screen_dev2_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_dev2_label_main_main_default
style_device_screen_dev2_label_main_main_default = lv.style_t()
style_device_screen_dev2_label_main_main_default.init()
style_device_screen_dev2_label_main_main_default.set_radius(0)
style_device_screen_dev2_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev2_label_main_main_default.set_bg_opa(0)
style_device_screen_dev2_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_screen_dev2_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev2_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev2_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev2_label_main_main_default.set_text_letter_space(0)
style_device_screen_dev2_label_main_main_default.set_text_line_space(0)
style_device_screen_dev2_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev2_label_main_main_default.set_pad_left(0)
style_device_screen_dev2_label_main_main_default.set_pad_right(0)
style_device_screen_dev2_label_main_main_default.set_pad_top(0)
style_device_screen_dev2_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev2_label
device_screen_dev2_label.add_style(style_device_screen_dev2_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev2_icon_bg
device_screen_dev2_icon_bg = lv.label(device_screen_dev2_cont)
device_screen_dev2_icon_bg.set_pos(int(11),int(9))
device_screen_dev2_icon_bg.set_size(50,50)
device_screen_dev2_icon_bg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev2_icon_bg_main_main_default
style_device_screen_dev2_icon_bg_main_main_default = lv.style_t()
style_device_screen_dev2_icon_bg_main_main_default.init()
style_device_screen_dev2_icon_bg_main_main_default.set_radius(10)
style_device_screen_dev2_icon_bg_main_main_default.set_bg_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev2_icon_bg_main_main_default.set_bg_grad_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev2_icon_bg_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev2_icon_bg_main_main_default.set_bg_opa(255)
style_device_screen_dev2_icon_bg_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev2_icon_bg_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev2_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev2_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev2_icon_bg_main_main_default.set_text_letter_space(0)
style_device_screen_dev2_icon_bg_main_main_default.set_text_line_space(0)
style_device_screen_dev2_icon_bg_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev2_icon_bg_main_main_default.set_pad_left(0)
style_device_screen_dev2_icon_bg_main_main_default.set_pad_right(0)
style_device_screen_dev2_icon_bg_main_main_default.set_pad_top(0)
style_device_screen_dev2_icon_bg_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev2_icon_bg
device_screen_dev2_icon_bg.add_style(style_device_screen_dev2_icon_bg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev2_icon
device_screen_dev2_icon = lv.img(device_screen_dev2_cont)
device_screen_dev2_icon.set_pos(int(20),int(18))
device_screen_dev2_icon.set_size(32,32)
device_screen_dev2_icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev2_icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png','rb') as f:
        device_screen_dev2_icon_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png')
    sys.exit()

device_screen_dev2_icon_img = lv.img_dsc_t({
  'data_size': len(device_screen_dev2_icon_img_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': device_screen_dev2_icon_img_data
})

device_screen_dev2_icon.set_src(device_screen_dev2_icon_img)
device_screen_dev2_icon.set_pivot(0,0)
device_screen_dev2_icon.set_angle(0)
# create style style_device_screen_dev2_icon_main_main_default
style_device_screen_dev2_icon_main_main_default = lv.style_t()
style_device_screen_dev2_icon_main_main_default.init()
style_device_screen_dev2_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_device_screen_dev2_icon_main_main_default.set_img_recolor_opa(0)
style_device_screen_dev2_icon_main_main_default.set_img_opa(255)

# add style for device_screen_dev2_icon
device_screen_dev2_icon.add_style(style_device_screen_dev2_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev2_btn
device_screen_dev2_btn = lv.btn(device_screen_dev2_cont)
device_screen_dev2_btn.set_pos(int(0),int(0))
device_screen_dev2_btn.set_size(145,110)
device_screen_dev2_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev2_btn_main_main_default
style_device_screen_dev2_btn_main_main_default = lv.style_t()
style_device_screen_dev2_btn_main_main_default.init()
style_device_screen_dev2_btn_main_main_default.set_radius(0)
style_device_screen_dev2_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev2_btn_main_main_default.set_bg_opa(0)
style_device_screen_dev2_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_btn_main_main_default.set_border_width(0)
style_device_screen_dev2_btn_main_main_default.set_border_opa(255)
style_device_screen_dev2_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev2_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev2_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev2_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev2_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_dev2_btn
device_screen_dev2_btn.add_style(style_device_screen_dev2_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_dev2_cont_main_main_default
style_device_screen_dev2_cont_main_main_default = lv.style_t()
style_device_screen_dev2_cont_main_main_default.init()
style_device_screen_dev2_cont_main_main_default.set_radius(10)
style_device_screen_dev2_cont_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev2_cont_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev2_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev2_cont_main_main_default.set_bg_opa(255)
style_device_screen_dev2_cont_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev2_cont_main_main_default.set_border_width(0)
style_device_screen_dev2_cont_main_main_default.set_border_opa(0)
style_device_screen_dev2_cont_main_main_default.set_pad_left(0)
style_device_screen_dev2_cont_main_main_default.set_pad_right(0)
style_device_screen_dev2_cont_main_main_default.set_pad_top(0)
style_device_screen_dev2_cont_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev2_cont
device_screen_dev2_cont.add_style(style_device_screen_dev2_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev3_cont
device_screen_dev3_cont = lv.obj(device_screen)
device_screen_dev3_cont.set_pos(int(10),int(154))
device_screen_dev3_cont.set_size(145,110)
device_screen_dev3_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create device_screen_dev3_label
device_screen_dev3_label = lv.label(device_screen_dev3_cont)
device_screen_dev3_label.set_pos(int(1),int(65))
device_screen_dev3_label.set_size(144,34)
device_screen_dev3_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev3_label.set_text("room 3\n")
device_screen_dev3_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_dev3_label_main_main_default
style_device_screen_dev3_label_main_main_default = lv.style_t()
style_device_screen_dev3_label_main_main_default.init()
style_device_screen_dev3_label_main_main_default.set_radius(0)
style_device_screen_dev3_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev3_label_main_main_default.set_bg_opa(0)
style_device_screen_dev3_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_screen_dev3_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev3_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev3_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev3_label_main_main_default.set_text_letter_space(0)
style_device_screen_dev3_label_main_main_default.set_text_line_space(0)
style_device_screen_dev3_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev3_label_main_main_default.set_pad_left(0)
style_device_screen_dev3_label_main_main_default.set_pad_right(0)
style_device_screen_dev3_label_main_main_default.set_pad_top(0)
style_device_screen_dev3_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev3_label
device_screen_dev3_label.add_style(style_device_screen_dev3_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev3_icon_bg
device_screen_dev3_icon_bg = lv.label(device_screen_dev3_cont)
device_screen_dev3_icon_bg.set_pos(int(11),int(9))
device_screen_dev3_icon_bg.set_size(50,50)
device_screen_dev3_icon_bg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev3_icon_bg_main_main_default
style_device_screen_dev3_icon_bg_main_main_default = lv.style_t()
style_device_screen_dev3_icon_bg_main_main_default.init()
style_device_screen_dev3_icon_bg_main_main_default.set_radius(10)
style_device_screen_dev3_icon_bg_main_main_default.set_bg_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev3_icon_bg_main_main_default.set_bg_grad_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev3_icon_bg_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev3_icon_bg_main_main_default.set_bg_opa(255)
style_device_screen_dev3_icon_bg_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev3_icon_bg_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev3_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev3_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev3_icon_bg_main_main_default.set_text_letter_space(0)
style_device_screen_dev3_icon_bg_main_main_default.set_text_line_space(0)
style_device_screen_dev3_icon_bg_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev3_icon_bg_main_main_default.set_pad_left(0)
style_device_screen_dev3_icon_bg_main_main_default.set_pad_right(0)
style_device_screen_dev3_icon_bg_main_main_default.set_pad_top(0)
style_device_screen_dev3_icon_bg_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev3_icon_bg
device_screen_dev3_icon_bg.add_style(style_device_screen_dev3_icon_bg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev3_icon
device_screen_dev3_icon = lv.img(device_screen_dev3_cont)
device_screen_dev3_icon.set_pos(int(20),int(18))
device_screen_dev3_icon.set_size(32,32)
device_screen_dev3_icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev3_icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png','rb') as f:
        device_screen_dev3_icon_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png')
    sys.exit()

device_screen_dev3_icon_img = lv.img_dsc_t({
  'data_size': len(device_screen_dev3_icon_img_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': device_screen_dev3_icon_img_data
})

device_screen_dev3_icon.set_src(device_screen_dev3_icon_img)
device_screen_dev3_icon.set_pivot(0,0)
device_screen_dev3_icon.set_angle(0)
# create style style_device_screen_dev3_icon_main_main_default
style_device_screen_dev3_icon_main_main_default = lv.style_t()
style_device_screen_dev3_icon_main_main_default.init()
style_device_screen_dev3_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_device_screen_dev3_icon_main_main_default.set_img_recolor_opa(0)
style_device_screen_dev3_icon_main_main_default.set_img_opa(255)

# add style for device_screen_dev3_icon
device_screen_dev3_icon.add_style(style_device_screen_dev3_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev3_btn
device_screen_dev3_btn = lv.btn(device_screen_dev3_cont)
device_screen_dev3_btn.set_pos(int(0),int(0))
device_screen_dev3_btn.set_size(145,110)
device_screen_dev3_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev3_btn_main_main_default
style_device_screen_dev3_btn_main_main_default = lv.style_t()
style_device_screen_dev3_btn_main_main_default.init()
style_device_screen_dev3_btn_main_main_default.set_radius(0)
style_device_screen_dev3_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev3_btn_main_main_default.set_bg_opa(0)
style_device_screen_dev3_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_btn_main_main_default.set_border_width(0)
style_device_screen_dev3_btn_main_main_default.set_border_opa(255)
style_device_screen_dev3_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev3_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev3_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev3_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev3_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_dev3_btn
device_screen_dev3_btn.add_style(style_device_screen_dev3_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_dev3_cont_main_main_default
style_device_screen_dev3_cont_main_main_default = lv.style_t()
style_device_screen_dev3_cont_main_main_default.init()
style_device_screen_dev3_cont_main_main_default.set_radius(10)
style_device_screen_dev3_cont_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev3_cont_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev3_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev3_cont_main_main_default.set_bg_opa(255)
style_device_screen_dev3_cont_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev3_cont_main_main_default.set_border_width(0)
style_device_screen_dev3_cont_main_main_default.set_border_opa(0)
style_device_screen_dev3_cont_main_main_default.set_pad_left(0)
style_device_screen_dev3_cont_main_main_default.set_pad_right(0)
style_device_screen_dev3_cont_main_main_default.set_pad_top(0)
style_device_screen_dev3_cont_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev3_cont
device_screen_dev3_cont.add_style(style_device_screen_dev3_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev4_cont
device_screen_dev4_cont = lv.obj(device_screen)
device_screen_dev4_cont.set_pos(int(165),int(154))
device_screen_dev4_cont.set_size(145,110)
device_screen_dev4_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create device_screen_dev4_label
device_screen_dev4_label = lv.label(device_screen_dev4_cont)
device_screen_dev4_label.set_pos(int(1),int(65))
device_screen_dev4_label.set_size(144,34)
device_screen_dev4_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev4_label.set_text("room 4")
device_screen_dev4_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_dev4_label_main_main_default
style_device_screen_dev4_label_main_main_default = lv.style_t()
style_device_screen_dev4_label_main_main_default.init()
style_device_screen_dev4_label_main_main_default.set_radius(0)
style_device_screen_dev4_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev4_label_main_main_default.set_bg_opa(0)
style_device_screen_dev4_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_screen_dev4_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev4_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev4_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev4_label_main_main_default.set_text_letter_space(0)
style_device_screen_dev4_label_main_main_default.set_text_line_space(0)
style_device_screen_dev4_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev4_label_main_main_default.set_pad_left(0)
style_device_screen_dev4_label_main_main_default.set_pad_right(0)
style_device_screen_dev4_label_main_main_default.set_pad_top(0)
style_device_screen_dev4_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev4_label
device_screen_dev4_label.add_style(style_device_screen_dev4_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev4_icon_bg
device_screen_dev4_icon_bg = lv.label(device_screen_dev4_cont)
device_screen_dev4_icon_bg.set_pos(int(11),int(9))
device_screen_dev4_icon_bg.set_size(50,50)
device_screen_dev4_icon_bg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev4_icon_bg_main_main_default
style_device_screen_dev4_icon_bg_main_main_default = lv.style_t()
style_device_screen_dev4_icon_bg_main_main_default.init()
style_device_screen_dev4_icon_bg_main_main_default.set_radius(10)
style_device_screen_dev4_icon_bg_main_main_default.set_bg_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev4_icon_bg_main_main_default.set_bg_grad_color(lv.color_make(0x42,0x42,0x42))
style_device_screen_dev4_icon_bg_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev4_icon_bg_main_main_default.set_bg_opa(255)
style_device_screen_dev4_icon_bg_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev4_icon_bg_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev4_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev4_icon_bg_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev4_icon_bg_main_main_default.set_text_letter_space(0)
style_device_screen_dev4_icon_bg_main_main_default.set_text_line_space(0)
style_device_screen_dev4_icon_bg_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_dev4_icon_bg_main_main_default.set_pad_left(0)
style_device_screen_dev4_icon_bg_main_main_default.set_pad_right(0)
style_device_screen_dev4_icon_bg_main_main_default.set_pad_top(0)
style_device_screen_dev4_icon_bg_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev4_icon_bg
device_screen_dev4_icon_bg.add_style(style_device_screen_dev4_icon_bg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev4_icon
device_screen_dev4_icon = lv.img(device_screen_dev4_cont)
device_screen_dev4_icon.set_pos(int(20),int(18))
device_screen_dev4_icon.set_size(32,32)
device_screen_dev4_icon.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_dev4_icon.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png','rb') as f:
        device_screen_dev4_icon_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp643627450.png')
    sys.exit()

device_screen_dev4_icon_img = lv.img_dsc_t({
  'data_size': len(device_screen_dev4_icon_img_data),
  'header': {'always_zero': 0, 'w': 32, 'h': 32, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': device_screen_dev4_icon_img_data
})

device_screen_dev4_icon.set_src(device_screen_dev4_icon_img)
device_screen_dev4_icon.set_pivot(0,0)
device_screen_dev4_icon.set_angle(0)
# create style style_device_screen_dev4_icon_main_main_default
style_device_screen_dev4_icon_main_main_default = lv.style_t()
style_device_screen_dev4_icon_main_main_default.init()
style_device_screen_dev4_icon_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_device_screen_dev4_icon_main_main_default.set_img_recolor_opa(0)
style_device_screen_dev4_icon_main_main_default.set_img_opa(255)

# add style for device_screen_dev4_icon
device_screen_dev4_icon.add_style(style_device_screen_dev4_icon_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_screen_dev4_btn
device_screen_dev4_btn = lv.btn(device_screen_dev4_cont)
device_screen_dev4_btn.set_pos(int(0),int(0))
device_screen_dev4_btn.set_size(145,110)
device_screen_dev4_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_dev4_btn_main_main_default
style_device_screen_dev4_btn_main_main_default = lv.style_t()
style_device_screen_dev4_btn_main_main_default.init()
style_device_screen_dev4_btn_main_main_default.set_radius(0)
style_device_screen_dev4_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev4_btn_main_main_default.set_bg_opa(0)
style_device_screen_dev4_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_btn_main_main_default.set_border_width(0)
style_device_screen_dev4_btn_main_main_default.set_border_opa(255)
style_device_screen_dev4_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_dev4_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_screen_dev4_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_screen_dev4_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_dev4_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_dev4_btn
device_screen_dev4_btn.add_style(style_device_screen_dev4_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_dev4_cont_main_main_default
style_device_screen_dev4_cont_main_main_default = lv.style_t()
style_device_screen_dev4_cont_main_main_default.init()
style_device_screen_dev4_cont_main_main_default.set_radius(10)
style_device_screen_dev4_cont_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev4_cont_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_screen_dev4_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_screen_dev4_cont_main_main_default.set_bg_opa(255)
style_device_screen_dev4_cont_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_dev4_cont_main_main_default.set_border_width(0)
style_device_screen_dev4_cont_main_main_default.set_border_opa(0)
style_device_screen_dev4_cont_main_main_default.set_pad_left(0)
style_device_screen_dev4_cont_main_main_default.set_pad_right(0)
style_device_screen_dev4_cont_main_main_default.set_pad_top(0)
style_device_screen_dev4_cont_main_main_default.set_pad_bottom(0)

# add style for device_screen_dev4_cont
device_screen_dev4_cont.add_style(style_device_screen_dev4_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop
screen_top_drop = lv.obj()
screen_top_drop.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_top_drop_main_main_default
style_screen_top_drop_main_main_default = lv.style_t()
style_screen_top_drop_main_main_default.init()
style_screen_top_drop_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_main_main_default.set_bg_opa(255)

# add style for screen_top_drop
screen_top_drop.add_style(style_screen_top_drop_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop_network_btn
screen_top_drop_network_btn = lv.imgbtn(screen_top_drop)
screen_top_drop_network_btn.set_pos(int(35),int(20))
screen_top_drop_network_btn.set_size(50,50)
screen_top_drop_network_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png','rb') as f:
        screen_top_drop_network_btn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png')
    sys.exit()

screen_top_drop_network_btn_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_network_btn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_network_btn_imgReleased_data
})
screen_top_drop_network_btn.set_src(lv.imgbtn.STATE.RELEASED, None, screen_top_drop_network_btn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png','rb') as f:
        screen_top_drop_network_btn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png')
    sys.exit()

screen_top_drop_network_btn_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_network_btn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_network_btn_imgPressed_data
})
screen_top_drop_network_btn.set_src(lv.imgbtn.STATE.PRESSED, None, screen_top_drop_network_btn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png','rb') as f:
        screen_top_drop_network_btn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png')
    sys.exit()

screen_top_drop_network_btn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_network_btn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_network_btn_imgCheckedReleased_data
})
screen_top_drop_network_btn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, screen_top_drop_network_btn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png','rb') as f:
        screen_top_drop_network_btn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp993382904.png')
    sys.exit()

screen_top_drop_network_btn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_network_btn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_network_btn_imgCheckedPressed_data
})
screen_top_drop_network_btn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, screen_top_drop_network_btn_imgCheckedPressed, None)

screen_top_drop_network_btn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_top_drop_network_btn_main_main_default
style_screen_top_drop_network_btn_main_main_default = lv.style_t()
style_screen_top_drop_network_btn_main_main_default.init()
style_screen_top_drop_network_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_top_drop_network_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_network_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_network_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_network_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_network_btn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_top_drop_network_btn_main_main_default.set_img_recolor_opa(0)
style_screen_top_drop_network_btn_main_main_default.set_img_opa(255)

# add style for screen_top_drop_network_btn
screen_top_drop_network_btn.add_style(style_screen_top_drop_network_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_top_drop_network_btn_main_main_pressed
style_screen_top_drop_network_btn_main_main_pressed = lv.style_t()
style_screen_top_drop_network_btn_main_main_pressed.init()
style_screen_top_drop_network_btn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_network_btn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_network_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_network_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_network_btn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_network_btn_main_main_pressed.set_img_recolor_opa(0)
style_screen_top_drop_network_btn_main_main_pressed.set_img_opa(255)

# add style for screen_top_drop_network_btn
screen_top_drop_network_btn.add_style(style_screen_top_drop_network_btn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_top_drop_network_btn_main_main_checked
style_screen_top_drop_network_btn_main_main_checked = lv.style_t()
style_screen_top_drop_network_btn_main_main_checked.init()
style_screen_top_drop_network_btn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_network_btn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_network_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_network_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_network_btn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_network_btn_main_main_checked.set_img_recolor_opa(0)
style_screen_top_drop_network_btn_main_main_checked.set_img_opa(255)

# add style for screen_top_drop_network_btn
screen_top_drop_network_btn.add_style(style_screen_top_drop_network_btn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)


# create screen_top_drop_label_network
screen_top_drop_label_network = lv.label(screen_top_drop)
screen_top_drop_label_network.set_pos(int(19),int(75))
screen_top_drop_label_network.set_size(83,20)
screen_top_drop_label_network.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_top_drop_label_network.set_text("Network")
screen_top_drop_label_network.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_top_drop_label_network_main_main_default
style_screen_top_drop_label_network_main_main_default = lv.style_t()
style_screen_top_drop_label_network_main_main_default.init()
style_screen_top_drop_label_network_main_main_default.set_radius(0)
style_screen_top_drop_label_network_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_network_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_network_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_label_network_main_main_default.set_bg_opa(0)
style_screen_top_drop_label_network_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_top_drop_label_network_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_label_network_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_label_network_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_label_network_main_main_default.set_text_letter_space(0)
style_screen_top_drop_label_network_main_main_default.set_text_line_space(0)
style_screen_top_drop_label_network_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_label_network_main_main_default.set_pad_left(0)
style_screen_top_drop_label_network_main_main_default.set_pad_right(0)
style_screen_top_drop_label_network_main_main_default.set_pad_top(0)
style_screen_top_drop_label_network_main_main_default.set_pad_bottom(0)

# add style for screen_top_drop_label_network
screen_top_drop_label_network.add_style(style_screen_top_drop_label_network_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop_setting_btn
screen_top_drop_setting_btn = lv.imgbtn(screen_top_drop)
screen_top_drop_setting_btn.set_pos(int(135),int(22))
screen_top_drop_setting_btn.set_size(50,50)
screen_top_drop_setting_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png','rb') as f:
        screen_top_drop_setting_btn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png')
    sys.exit()

screen_top_drop_setting_btn_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_setting_btn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_setting_btn_imgReleased_data
})
screen_top_drop_setting_btn.set_src(lv.imgbtn.STATE.RELEASED, None, screen_top_drop_setting_btn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png','rb') as f:
        screen_top_drop_setting_btn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png')
    sys.exit()

screen_top_drop_setting_btn_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_setting_btn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_setting_btn_imgPressed_data
})
screen_top_drop_setting_btn.set_src(lv.imgbtn.STATE.PRESSED, None, screen_top_drop_setting_btn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png','rb') as f:
        screen_top_drop_setting_btn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png')
    sys.exit()

screen_top_drop_setting_btn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_setting_btn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_setting_btn_imgCheckedReleased_data
})
screen_top_drop_setting_btn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, screen_top_drop_setting_btn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png','rb') as f:
        screen_top_drop_setting_btn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-251646237.png')
    sys.exit()

screen_top_drop_setting_btn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_setting_btn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_setting_btn_imgCheckedPressed_data
})
screen_top_drop_setting_btn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, screen_top_drop_setting_btn_imgCheckedPressed, None)

screen_top_drop_setting_btn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_top_drop_setting_btn_main_main_default
style_screen_top_drop_setting_btn_main_main_default = lv.style_t()
style_screen_top_drop_setting_btn_main_main_default.init()
style_screen_top_drop_setting_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_top_drop_setting_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_setting_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_setting_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_setting_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_setting_btn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_top_drop_setting_btn_main_main_default.set_img_recolor_opa(0)
style_screen_top_drop_setting_btn_main_main_default.set_img_opa(255)

# add style for screen_top_drop_setting_btn
screen_top_drop_setting_btn.add_style(style_screen_top_drop_setting_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_top_drop_setting_btn_main_main_pressed
style_screen_top_drop_setting_btn_main_main_pressed = lv.style_t()
style_screen_top_drop_setting_btn_main_main_pressed.init()
style_screen_top_drop_setting_btn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_setting_btn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_setting_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_setting_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_setting_btn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_setting_btn_main_main_pressed.set_img_recolor_opa(0)
style_screen_top_drop_setting_btn_main_main_pressed.set_img_opa(255)

# add style for screen_top_drop_setting_btn
screen_top_drop_setting_btn.add_style(style_screen_top_drop_setting_btn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_top_drop_setting_btn_main_main_checked
style_screen_top_drop_setting_btn_main_main_checked = lv.style_t()
style_screen_top_drop_setting_btn_main_main_checked.init()
style_screen_top_drop_setting_btn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_setting_btn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_setting_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_setting_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_setting_btn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_setting_btn_main_main_checked.set_img_recolor_opa(0)
style_screen_top_drop_setting_btn_main_main_checked.set_img_opa(255)

# add style for screen_top_drop_setting_btn
screen_top_drop_setting_btn.add_style(style_screen_top_drop_setting_btn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)


# create screen_top_drop_label_setting
screen_top_drop_label_setting = lv.label(screen_top_drop)
screen_top_drop_label_setting.set_pos(int(118),int(75))
screen_top_drop_label_setting.set_size(83,20)
screen_top_drop_label_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_top_drop_label_setting.set_text("Settings")
screen_top_drop_label_setting.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_top_drop_label_setting_main_main_default
style_screen_top_drop_label_setting_main_main_default = lv.style_t()
style_screen_top_drop_label_setting_main_main_default.init()
style_screen_top_drop_label_setting_main_main_default.set_radius(0)
style_screen_top_drop_label_setting_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_setting_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_setting_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_label_setting_main_main_default.set_bg_opa(0)
style_screen_top_drop_label_setting_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_top_drop_label_setting_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_label_setting_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_label_setting_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_label_setting_main_main_default.set_text_letter_space(0)
style_screen_top_drop_label_setting_main_main_default.set_text_line_space(0)
style_screen_top_drop_label_setting_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_label_setting_main_main_default.set_pad_left(0)
style_screen_top_drop_label_setting_main_main_default.set_pad_right(0)
style_screen_top_drop_label_setting_main_main_default.set_pad_top(0)
style_screen_top_drop_label_setting_main_main_default.set_pad_bottom(0)

# add style for screen_top_drop_label_setting
screen_top_drop_label_setting.add_style(style_screen_top_drop_label_setting_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop_upgrade_scene_btn
screen_top_drop_upgrade_scene_btn = lv.imgbtn(screen_top_drop)
screen_top_drop_upgrade_scene_btn.set_pos(int(235),int(20))
screen_top_drop_upgrade_scene_btn.set_size(50,50)
screen_top_drop_upgrade_scene_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png','rb') as f:
        screen_top_drop_upgrade_scene_btn_imgReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png')
    sys.exit()

screen_top_drop_upgrade_scene_btn_imgReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_upgrade_scene_btn_imgReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_upgrade_scene_btn_imgReleased_data
})
screen_top_drop_upgrade_scene_btn.set_src(lv.imgbtn.STATE.RELEASED, None, screen_top_drop_upgrade_scene_btn_imgReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png','rb') as f:
        screen_top_drop_upgrade_scene_btn_imgPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png')
    sys.exit()

screen_top_drop_upgrade_scene_btn_imgPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_upgrade_scene_btn_imgPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_upgrade_scene_btn_imgPressed_data
})
screen_top_drop_upgrade_scene_btn.set_src(lv.imgbtn.STATE.PRESSED, None, screen_top_drop_upgrade_scene_btn_imgPressed, None)


try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png','rb') as f:
        screen_top_drop_upgrade_scene_btn_imgCheckedReleased_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png')
    sys.exit()

screen_top_drop_upgrade_scene_btn_imgCheckedReleased = lv.img_dsc_t({
  'data_size': len(screen_top_drop_upgrade_scene_btn_imgCheckedReleased_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_upgrade_scene_btn_imgCheckedReleased_data
})
screen_top_drop_upgrade_scene_btn.set_src(lv.imgbtn.STATE.CHECKED_RELEASED, None, screen_top_drop_upgrade_scene_btn_imgCheckedReleased, None)

try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png','rb') as f:
        screen_top_drop_upgrade_scene_btn_imgCheckedPressed_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-471419796.png')
    sys.exit()

screen_top_drop_upgrade_scene_btn_imgCheckedPressed = lv.img_dsc_t({
  'data_size': len(screen_top_drop_upgrade_scene_btn_imgCheckedPressed_data),
  'header': {'always_zero': 0, 'w': 50, 'h': 50, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_top_drop_upgrade_scene_btn_imgCheckedPressed_data
})
screen_top_drop_upgrade_scene_btn.set_src(lv.imgbtn.STATE.CHECKED_PRESSED, None, screen_top_drop_upgrade_scene_btn_imgCheckedPressed, None)

screen_top_drop_upgrade_scene_btn.add_flag(lv.obj.FLAG.CHECKABLE)
# create style style_screen_top_drop_upgrade_scene_btn_main_main_default
style_screen_top_drop_upgrade_scene_btn_main_main_default = lv.style_t()
style_screen_top_drop_upgrade_scene_btn_main_main_default.init()
style_screen_top_drop_upgrade_scene_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_top_drop_upgrade_scene_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_upgrade_scene_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_upgrade_scene_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_upgrade_scene_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_upgrade_scene_btn_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_top_drop_upgrade_scene_btn_main_main_default.set_img_recolor_opa(0)
style_screen_top_drop_upgrade_scene_btn_main_main_default.set_img_opa(255)

# add style for screen_top_drop_upgrade_scene_btn
screen_top_drop_upgrade_scene_btn.add_style(style_screen_top_drop_upgrade_scene_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_top_drop_upgrade_scene_btn_main_main_pressed
style_screen_top_drop_upgrade_scene_btn_main_main_pressed = lv.style_t()
style_screen_top_drop_upgrade_scene_btn_main_main_pressed.init()
style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_img_recolor_opa(0)
style_screen_top_drop_upgrade_scene_btn_main_main_pressed.set_img_opa(255)

# add style for screen_top_drop_upgrade_scene_btn
screen_top_drop_upgrade_scene_btn.add_style(style_screen_top_drop_upgrade_scene_btn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

# create style style_screen_top_drop_upgrade_scene_btn_main_main_checked
style_screen_top_drop_upgrade_scene_btn_main_main_checked = lv.style_t()
style_screen_top_drop_upgrade_scene_btn_main_main_checked.init()
style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_text_color(lv.color_make(0xFF,0x33,0xFF))
try:
    style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_img_recolor(lv.color_make(0x00,0x00,0x00))
style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_img_recolor_opa(0)
style_screen_top_drop_upgrade_scene_btn_main_main_checked.set_img_opa(255)

# add style for screen_top_drop_upgrade_scene_btn
screen_top_drop_upgrade_scene_btn.add_style(style_screen_top_drop_upgrade_scene_btn_main_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)


# create screen_top_drop_label_upgrade_scene
screen_top_drop_label_upgrade_scene = lv.label(screen_top_drop)
screen_top_drop_label_upgrade_scene.set_pos(int(220),int(75))
screen_top_drop_label_upgrade_scene.set_size(83,20)
screen_top_drop_label_upgrade_scene.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_top_drop_label_upgrade_scene.set_text("Refresh\n")
screen_top_drop_label_upgrade_scene.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_top_drop_label_upgrade_scene_main_main_default
style_screen_top_drop_label_upgrade_scene_main_main_default = lv.style_t()
style_screen_top_drop_label_upgrade_scene_main_main_default.init()
style_screen_top_drop_label_upgrade_scene_main_main_default.set_radius(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_upgrade_scene_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_upgrade_scene_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_bg_opa(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_letter_space(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_line_space(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_pad_left(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_pad_right(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_pad_top(0)
style_screen_top_drop_label_upgrade_scene_main_main_default.set_pad_bottom(0)

# add style for screen_top_drop_label_upgrade_scene
screen_top_drop_label_upgrade_scene.add_style(style_screen_top_drop_label_upgrade_scene_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop_soud_con
screen_top_drop_soud_con = lv.obj(screen_top_drop)
screen_top_drop_soud_con.set_pos(int(20),int(105))
screen_top_drop_soud_con.set_size(280,70)
screen_top_drop_soud_con.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

# create screen_top_drop_label_volume
screen_top_drop_label_volume = lv.label(screen_top_drop_soud_con)
screen_top_drop_label_volume.set_pos(int(90),int(14))
screen_top_drop_label_volume.set_size(100,20)
screen_top_drop_label_volume.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_top_drop_label_volume.set_text("Volume")
screen_top_drop_label_volume.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_top_drop_label_volume_main_main_default
style_screen_top_drop_label_volume_main_main_default = lv.style_t()
style_screen_top_drop_label_volume_main_main_default.init()
style_screen_top_drop_label_volume_main_main_default.set_radius(0)
style_screen_top_drop_label_volume_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_volume_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_label_volume_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_label_volume_main_main_default.set_bg_opa(0)
style_screen_top_drop_label_volume_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_top_drop_label_volume_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_top_drop_label_volume_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_top_drop_label_volume_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_top_drop_label_volume_main_main_default.set_text_letter_space(0)
style_screen_top_drop_label_volume_main_main_default.set_text_line_space(0)
style_screen_top_drop_label_volume_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_top_drop_label_volume_main_main_default.set_pad_left(0)
style_screen_top_drop_label_volume_main_main_default.set_pad_right(0)
style_screen_top_drop_label_volume_main_main_default.set_pad_top(0)
style_screen_top_drop_label_volume_main_main_default.set_pad_bottom(0)

# add style for screen_top_drop_label_volume
screen_top_drop_label_volume.add_style(style_screen_top_drop_label_volume_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_top_drop_slider_soud
screen_top_drop_slider_soud = lv.slider(screen_top_drop_soud_con)
screen_top_drop_slider_soud.set_pos(int(15),int(46))
screen_top_drop_slider_soud.set_size(250,6)
screen_top_drop_slider_soud.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_top_drop_slider_soud.set_range(0, 100)
screen_top_drop_slider_soud.set_value(70, False)

# create style style_screen_top_drop_slider_soud_main_main_default
style_screen_top_drop_slider_soud_main_main_default = lv.style_t()
style_screen_top_drop_slider_soud_main_main_default.init()
style_screen_top_drop_slider_soud_main_main_default.set_radius(50)
style_screen_top_drop_slider_soud_main_main_default.set_bg_color(lv.color_make(0x60,0x6c,0x80))
style_screen_top_drop_slider_soud_main_main_default.set_bg_grad_color(lv.color_make(0x60,0x6c,0x80))
style_screen_top_drop_slider_soud_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_slider_soud_main_main_default.set_bg_opa(60)
style_screen_top_drop_slider_soud_main_main_default.set_outline_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_slider_soud_main_main_default.set_outline_width(0)
style_screen_top_drop_slider_soud_main_main_default.set_outline_opa(0)

# add style for screen_top_drop_slider_soud
screen_top_drop_slider_soud.add_style(style_screen_top_drop_slider_soud_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_top_drop_slider_soud_main_indicator_default
style_screen_top_drop_slider_soud_main_indicator_default = lv.style_t()
style_screen_top_drop_slider_soud_main_indicator_default.init()
style_screen_top_drop_slider_soud_main_indicator_default.set_radius(50)
style_screen_top_drop_slider_soud_main_indicator_default.set_bg_color(lv.color_make(0xff,0x4c,0x4c))
style_screen_top_drop_slider_soud_main_indicator_default.set_bg_grad_color(lv.color_make(0xff,0x4c,0x4c))
style_screen_top_drop_slider_soud_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_slider_soud_main_indicator_default.set_bg_opa(255)

# add style for screen_top_drop_slider_soud
screen_top_drop_slider_soud.add_style(style_screen_top_drop_slider_soud_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_screen_top_drop_slider_soud_main_knob_default
style_screen_top_drop_slider_soud_main_knob_default = lv.style_t()
style_screen_top_drop_slider_soud_main_knob_default.init()
style_screen_top_drop_slider_soud_main_knob_default.set_radius(50)
style_screen_top_drop_slider_soud_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_top_drop_slider_soud_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_top_drop_slider_soud_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_slider_soud_main_knob_default.set_bg_opa(255)

# add style for screen_top_drop_slider_soud
screen_top_drop_slider_soud.add_style(style_screen_top_drop_slider_soud_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

# create style style_screen_top_drop_soud_con_main_main_default
style_screen_top_drop_soud_con_main_main_default = lv.style_t()
style_screen_top_drop_soud_con_main_main_default.init()
style_screen_top_drop_soud_con_main_main_default.set_radius(5)
style_screen_top_drop_soud_con_main_main_default.set_bg_color(lv.color_make(0xd3,0xd3,0xd3))
style_screen_top_drop_soud_con_main_main_default.set_bg_grad_color(lv.color_make(0xd3,0xd3,0xd3))
style_screen_top_drop_soud_con_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_top_drop_soud_con_main_main_default.set_bg_opa(255)
style_screen_top_drop_soud_con_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_top_drop_soud_con_main_main_default.set_border_width(0)
style_screen_top_drop_soud_con_main_main_default.set_border_opa(255)
style_screen_top_drop_soud_con_main_main_default.set_pad_left(0)
style_screen_top_drop_soud_con_main_main_default.set_pad_right(0)
style_screen_top_drop_soud_con_main_main_default.set_pad_top(0)
style_screen_top_drop_soud_con_main_main_default.set_pad_bottom(0)

# add style for screen_top_drop_soud_con
screen_top_drop_soud_con.add_style(style_screen_top_drop_soud_con_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_wificonf
screen_wificonf = lv.obj()
screen_wificonf.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_wificonf_main_main_default
style_screen_wificonf_main_main_default = lv.style_t()
style_screen_wificonf_main_main_default.init()
style_screen_wificonf_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_wificonf_main_main_default.set_bg_opa(255)

# add style for screen_wificonf
screen_wificonf.add_style(style_screen_wificonf_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_wificonf_returnbg
screen_wificonf_returnbg = lv.img(screen_wificonf)
screen_wificonf_returnbg.set_pos(int(10),int(8))
screen_wificonf_returnbg.set_size(28,22)
screen_wificonf_returnbg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_wificonf_returnbg.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png','rb') as f:
        screen_wificonf_returnbg_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png')
    sys.exit()

screen_wificonf_returnbg_img = lv.img_dsc_t({
  'data_size': len(screen_wificonf_returnbg_img_data),
  'header': {'always_zero': 0, 'w': 28, 'h': 22, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_wificonf_returnbg_img_data
})

screen_wificonf_returnbg.set_src(screen_wificonf_returnbg_img)
screen_wificonf_returnbg.set_pivot(0,0)
screen_wificonf_returnbg.set_angle(0)
# create style style_screen_wificonf_returnbg_main_main_default
style_screen_wificonf_returnbg_main_main_default = lv.style_t()
style_screen_wificonf_returnbg_main_main_default.init()
style_screen_wificonf_returnbg_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_wificonf_returnbg_main_main_default.set_img_recolor_opa(0)
style_screen_wificonf_returnbg_main_main_default.set_img_opa(255)

# add style for screen_wificonf_returnbg
screen_wificonf_returnbg.add_style(style_screen_wificonf_returnbg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_wificonf_return_imgbtn
screen_wificonf_return_imgbtn = lv.btn(screen_wificonf)
screen_wificonf_return_imgbtn.set_pos(int(5),int(5))
screen_wificonf_return_imgbtn.set_size(60,32)
screen_wificonf_return_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_wificonf_return_imgbtn_main_main_default
style_screen_wificonf_return_imgbtn_main_main_default = lv.style_t()
style_screen_wificonf_return_imgbtn_main_main_default.init()
style_screen_wificonf_return_imgbtn_main_main_default.set_radius(0)
style_screen_wificonf_return_imgbtn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wificonf_return_imgbtn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wificonf_return_imgbtn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_wificonf_return_imgbtn_main_main_default.set_bg_opa(0)
style_screen_wificonf_return_imgbtn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wificonf_return_imgbtn_main_main_default.set_border_width(0)
style_screen_wificonf_return_imgbtn_main_main_default.set_border_opa(0)
style_screen_wificonf_return_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_wificonf_return_imgbtn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_wificonf_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_wificonf_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_wificonf_return_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_wificonf_return_imgbtn
screen_wificonf_return_imgbtn.add_style(style_screen_wificonf_return_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_wificonf_smartconfig_img
screen_wificonf_smartconfig_img = lv.img(screen_wificonf)
screen_wificonf_smartconfig_img.set_pos(int(107),int(95))
screen_wificonf_smartconfig_img.set_size(106,127)
screen_wificonf_smartconfig_img.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_wificonf_smartconfig_img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp2071605372.png','rb') as f:
        screen_wificonf_smartconfig_img_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp2071605372.png')
    sys.exit()

screen_wificonf_smartconfig_img_img = lv.img_dsc_t({
  'data_size': len(screen_wificonf_smartconfig_img_img_data),
  'header': {'always_zero': 0, 'w': 106, 'h': 127, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_wificonf_smartconfig_img_img_data
})

screen_wificonf_smartconfig_img.set_src(screen_wificonf_smartconfig_img_img)
screen_wificonf_smartconfig_img.set_pivot(0,0)
screen_wificonf_smartconfig_img.set_angle(0)
# create style style_screen_wificonf_smartconfig_img_main_main_default
style_screen_wificonf_smartconfig_img_main_main_default = lv.style_t()
style_screen_wificonf_smartconfig_img_main_main_default.init()
style_screen_wificonf_smartconfig_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_wificonf_smartconfig_img_main_main_default.set_img_recolor_opa(0)
style_screen_wificonf_smartconfig_img_main_main_default.set_img_opa(255)

# add style for screen_wificonf_smartconfig_img
screen_wificonf_smartconfig_img.add_style(style_screen_wificonf_smartconfig_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_wificonf_smartconfig_btn
screen_wificonf_smartconfig_btn = lv.btn(screen_wificonf)
screen_wificonf_smartconfig_btn.set_pos(int(103),int(217))
screen_wificonf_smartconfig_btn.set_size(115,28)
screen_wificonf_smartconfig_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_wificonf_smartconfig_btn_label = lv.label(screen_wificonf_smartconfig_btn)
screen_wificonf_smartconfig_btn_label.set_text("智能配网")
screen_wificonf_smartconfig_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_wificonf_smartconfig_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_wificonf_smartconfig_btn_main_main_default
style_screen_wificonf_smartconfig_btn_main_main_default = lv.style_t()
style_screen_wificonf_smartconfig_btn_main_main_default.init()
style_screen_wificonf_smartconfig_btn_main_main_default.set_radius(5)
style_screen_wificonf_smartconfig_btn_main_main_default.set_bg_color(lv.color_make(0xff,0xaa,0x23))
style_screen_wificonf_smartconfig_btn_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xaa,0x23))
style_screen_wificonf_smartconfig_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_wificonf_smartconfig_btn_main_main_default.set_bg_opa(255)
style_screen_wificonf_smartconfig_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_wificonf_smartconfig_btn_main_main_default.set_border_width(0)
style_screen_wificonf_smartconfig_btn_main_main_default.set_border_opa(0)
style_screen_wificonf_smartconfig_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_wificonf_smartconfig_btn_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_wificonf_smartconfig_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_wificonf_smartconfig_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_wificonf_smartconfig_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_wificonf_smartconfig_btn
screen_wificonf_smartconfig_btn.add_style(style_screen_wificonf_smartconfig_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_setting
screen_setting = lv.obj()
screen_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_setting_main_main_default
style_screen_setting_main_main_default = lv.style_t()
style_screen_setting_main_main_default.init()
style_screen_setting_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_setting_main_main_default.set_bg_opa(255)

# add style for screen_setting
screen_setting.add_style(style_screen_setting_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_setting_returnimg
screen_setting_returnimg = lv.img(screen_setting)
screen_setting_returnimg.set_pos(int(10),int(8))
screen_setting_returnimg.set_size(28,22)
screen_setting_returnimg.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_setting_returnimg.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png','rb') as f:
        screen_setting_returnimg_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png')
    sys.exit()

screen_setting_returnimg_img = lv.img_dsc_t({
  'data_size': len(screen_setting_returnimg_img_data),
  'header': {'always_zero': 0, 'w': 28, 'h': 22, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': screen_setting_returnimg_img_data
})

screen_setting_returnimg.set_src(screen_setting_returnimg_img)
screen_setting_returnimg.set_pivot(0,0)
screen_setting_returnimg.set_angle(0)
# create style style_screen_setting_returnimg_main_main_default
style_screen_setting_returnimg_main_main_default = lv.style_t()
style_screen_setting_returnimg_main_main_default.init()
style_screen_setting_returnimg_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_screen_setting_returnimg_main_main_default.set_img_recolor_opa(0)
style_screen_setting_returnimg_main_main_default.set_img_opa(255)

# add style for screen_setting_returnimg
screen_setting_returnimg.add_style(style_screen_setting_returnimg_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_setting_return_imgbtn
screen_setting_return_imgbtn = lv.btn(screen_setting)
screen_setting_return_imgbtn.set_pos(int(5),int(5))
screen_setting_return_imgbtn.set_size(60,30)
screen_setting_return_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_setting_return_imgbtn_main_main_default
style_screen_setting_return_imgbtn_main_main_default = lv.style_t()
style_screen_setting_return_imgbtn_main_main_default.init()
style_screen_setting_return_imgbtn_main_main_default.set_radius(0)
style_screen_setting_return_imgbtn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_setting_return_imgbtn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_setting_return_imgbtn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_setting_return_imgbtn_main_main_default.set_bg_opa(0)
style_screen_setting_return_imgbtn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_setting_return_imgbtn_main_main_default.set_border_width(0)
style_screen_setting_return_imgbtn_main_main_default.set_border_opa(0)
style_screen_setting_return_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_setting_return_imgbtn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_screen_setting_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_setting_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_setting_return_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_setting_return_imgbtn
screen_setting_return_imgbtn.add_style(style_screen_setting_return_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_setting_label_set
screen_setting_label_set = lv.label(screen_setting)
screen_setting_label_set.set_pos(int(110),int(10))
screen_setting_label_set.set_size(100,20)
screen_setting_label_set.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_setting_label_set.set_text("Settings\n")
screen_setting_label_set.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_setting_label_set_main_main_default
style_screen_setting_label_set_main_main_default = lv.style_t()
style_screen_setting_label_set_main_main_default.init()
style_screen_setting_label_set_main_main_default.set_radius(0)
style_screen_setting_label_set_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_setting_label_set_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_setting_label_set_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_setting_label_set_main_main_default.set_bg_opa(0)
style_screen_setting_label_set_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_setting_label_set_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_screen_setting_label_set_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_setting_label_set_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_setting_label_set_main_main_default.set_text_letter_space(0)
style_screen_setting_label_set_main_main_default.set_text_line_space(0)
style_screen_setting_label_set_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_setting_label_set_main_main_default.set_pad_left(0)
style_screen_setting_label_set_main_main_default.set_pad_right(0)
style_screen_setting_label_set_main_main_default.set_pad_top(0)
style_screen_setting_label_set_main_main_default.set_pad_bottom(0)

# add style for screen_setting_label_set
screen_setting_label_set.add_style(style_screen_setting_label_set_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_setting_list_1
screen_setting_list_1 = lv.list(screen_setting)
screen_setting_list_1.set_pos(int(0),int(40))
screen_setting_list_1.set_size(320,276)
screen_setting_list_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_setting_list_1_extra_btns_main_default
style_screen_setting_list_1_extra_btns_main_default = lv.style_t()
style_screen_setting_list_1_extra_btns_main_default.init()
style_screen_setting_list_1_extra_btns_main_default.set_radius(0)
style_screen_setting_list_1_extra_btns_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_screen_setting_list_1_extra_btns_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_screen_setting_list_1_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_setting_list_1_extra_btns_main_default.set_bg_opa(255)
style_screen_setting_list_1_extra_btns_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_setting_list_1_extra_btns_main_default.set_text_font(lv.font_simsun_16)
except AttributeError:
    try:
        style_screen_setting_list_1_extra_btns_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_setting_list_1_extra_btns_main_default.set_text_font(lv.font_montserrat_16)


screen_setting_list_1_btn_0 = screen_setting_list_1.add_btn(None, "Settings")

# add style for screen_setting_list_1_btn_0
screen_setting_list_1_btn_0.add_style(style_screen_setting_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_setting_list_1_btn_1 = screen_setting_list_1.add_btn(None, "Diasplay")

# add style for screen_setting_list_1_btn_1
screen_setting_list_1_btn_1.add_style(style_screen_setting_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_setting_list_1_btn_2 = screen_setting_list_1.add_btn(None, "System restart")

# add style for screen_setting_list_1_btn_2
screen_setting_list_1_btn_2.add_style(style_screen_setting_list_1_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_setting_list_1_main_main_default
style_screen_setting_list_1_main_main_default = lv.style_t()
style_screen_setting_list_1_main_main_default.init()
style_screen_setting_list_1_main_main_default.set_radius(0)
style_screen_setting_list_1_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_setting_list_1_main_main_default.set_bg_grad_color(lv.color_make(0x00,0x00,0x00))
style_screen_setting_list_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_setting_list_1_main_main_default.set_bg_opa(255)
style_screen_setting_list_1_main_main_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_screen_setting_list_1_main_main_default.set_border_width(0)
style_screen_setting_list_1_main_main_default.set_border_opa(255)
style_screen_setting_list_1_main_main_default.set_pad_left(0)
style_screen_setting_list_1_main_main_default.set_pad_right(0)
style_screen_setting_list_1_main_main_default.set_pad_top(0)
style_screen_setting_list_1_main_main_default.set_pad_bottom(5)

# add style for screen_setting_list_1
screen_setting_list_1.add_style(style_screen_setting_list_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_setting_list_1_main_scrollbar_default
style_screen_setting_list_1_main_scrollbar_default = lv.style_t()
style_screen_setting_list_1_main_scrollbar_default.init()
style_screen_setting_list_1_main_scrollbar_default.set_radius(0)
style_screen_setting_list_1_main_scrollbar_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_setting_list_1_main_scrollbar_default.set_bg_opa(0)

# add style for screen_setting_list_1
screen_setting_list_1.add_style(style_screen_setting_list_1_main_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)


# create device_rgblight
device_rgblight = lv.obj()
device_rgblight.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_main_main_default
style_device_rgblight_main_main_default = lv.style_t()
style_device_rgblight_main_main_default.init()
style_device_rgblight_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_device_rgblight_main_main_default.set_bg_opa(255)

# add style for device_rgblight
device_rgblight.add_style(style_device_rgblight_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_return_img
device_rgblight_return_img = lv.img(device_rgblight)
device_rgblight_return_img.set_pos(int(10),int(8))
device_rgblight_return_img.set_size(28,22)
device_rgblight_return_img.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_rgblight_return_img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png','rb') as f:
        device_rgblight_return_img_img_data = f.read()
except:
    print('Could not open C:\\NXP\\GUI-Guider-Projects\\esp32s3_320p_sr_86box_oman_demo_ui\\generated\\mPythonImages\\mp-1532420565.png')
    sys.exit()

device_rgblight_return_img_img = lv.img_dsc_t({
  'data_size': len(device_rgblight_return_img_img_data),
  'header': {'always_zero': 0, 'w': 28, 'h': 22, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': device_rgblight_return_img_img_data
})

device_rgblight_return_img.set_src(device_rgblight_return_img_img)
device_rgblight_return_img.set_pivot(0,0)
device_rgblight_return_img.set_angle(0)
# create style style_device_rgblight_return_img_main_main_default
style_device_rgblight_return_img_main_main_default = lv.style_t()
style_device_rgblight_return_img_main_main_default.init()
style_device_rgblight_return_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_device_rgblight_return_img_main_main_default.set_img_recolor_opa(0)
style_device_rgblight_return_img_main_main_default.set_img_opa(255)

# add style for device_rgblight_return_img
device_rgblight_return_img.add_style(style_device_rgblight_return_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_return_imgbtn
device_rgblight_return_imgbtn = lv.btn(device_rgblight)
device_rgblight_return_imgbtn.set_pos(int(5),int(5))
device_rgblight_return_imgbtn.set_size(60,32)
device_rgblight_return_imgbtn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_return_imgbtn_main_main_default
style_device_rgblight_return_imgbtn_main_main_default = lv.style_t()
style_device_rgblight_return_imgbtn_main_main_default.init()
style_device_rgblight_return_imgbtn_main_main_default.set_radius(0)
style_device_rgblight_return_imgbtn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_return_imgbtn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_return_imgbtn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_return_imgbtn_main_main_default.set_bg_opa(0)
style_device_rgblight_return_imgbtn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_return_imgbtn_main_main_default.set_border_width(0)
style_device_rgblight_return_imgbtn_main_main_default.set_border_opa(0)
style_device_rgblight_return_imgbtn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_rgblight_return_imgbtn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_rgblight_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_rgblight_return_imgbtn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_return_imgbtn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_rgblight_return_imgbtn
device_rgblight_return_imgbtn.add_style(style_device_rgblight_return_imgbtn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_light_sw
device_rgblight_light_sw = lv.switch(device_rgblight)
device_rgblight_light_sw.set_pos(int(26),int(53))
device_rgblight_light_sw.set_size(50,22)
device_rgblight_light_sw.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_light_sw_main_main_default
style_device_rgblight_light_sw_main_main_default = lv.style_t()
style_device_rgblight_light_sw_main_main_default.init()
style_device_rgblight_light_sw_main_main_default.set_radius(100)
style_device_rgblight_light_sw_main_main_default.set_bg_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_rgblight_light_sw_main_main_default.set_bg_grad_color(lv.color_make(0x2c,0x2c,0x2c))
style_device_rgblight_light_sw_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_light_sw_main_main_default.set_bg_opa(255)
style_device_rgblight_light_sw_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_light_sw_main_main_default.set_border_width(0)
style_device_rgblight_light_sw_main_main_default.set_border_opa(255)

# add style for device_rgblight_light_sw
device_rgblight_light_sw.add_style(style_device_rgblight_light_sw_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_rgblight_light_sw_main_indicator_checked
style_device_rgblight_light_sw_main_indicator_checked = lv.style_t()
style_device_rgblight_light_sw_main_indicator_checked.init()
style_device_rgblight_light_sw_main_indicator_checked.set_bg_color(lv.color_make(0xff,0xaa,0x23))
style_device_rgblight_light_sw_main_indicator_checked.set_bg_grad_color(lv.color_make(0xff,0xaa,0x23))
style_device_rgblight_light_sw_main_indicator_checked.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_light_sw_main_indicator_checked.set_bg_opa(255)
style_device_rgblight_light_sw_main_indicator_checked.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_light_sw_main_indicator_checked.set_border_width(0)
style_device_rgblight_light_sw_main_indicator_checked.set_border_opa(255)

# add style for device_rgblight_light_sw
device_rgblight_light_sw.add_style(style_device_rgblight_light_sw_main_indicator_checked, lv.PART.INDICATOR|lv.STATE.CHECKED)

# create style style_device_rgblight_light_sw_main_knob_default
style_device_rgblight_light_sw_main_knob_default = lv.style_t()
style_device_rgblight_light_sw_main_knob_default.init()
style_device_rgblight_light_sw_main_knob_default.set_radius(100)
style_device_rgblight_light_sw_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_device_rgblight_light_sw_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_device_rgblight_light_sw_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_light_sw_main_knob_default.set_bg_opa(255)
style_device_rgblight_light_sw_main_knob_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_light_sw_main_knob_default.set_border_width(0)
style_device_rgblight_light_sw_main_knob_default.set_border_opa(255)

# add style for device_rgblight_light_sw
device_rgblight_light_sw.add_style(style_device_rgblight_light_sw_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)


# create device_rgblight_color_btn_1
device_rgblight_color_btn_1 = lv.btn(device_rgblight)
device_rgblight_color_btn_1.set_pos(int(16),int(90))
device_rgblight_color_btn_1.set_size(32,32)
device_rgblight_color_btn_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_color_btn_1_main_main_default
style_device_rgblight_color_btn_1_main_main_default = lv.style_t()
style_device_rgblight_color_btn_1_main_main_default.init()
style_device_rgblight_color_btn_1_main_main_default.set_radius(30)
style_device_rgblight_color_btn_1_main_main_default.set_bg_color(lv.color_make(0xff,0x00,0xb2))
style_device_rgblight_color_btn_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0x00,0x88))
style_device_rgblight_color_btn_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_rgblight_color_btn_1_main_main_default.set_bg_opa(255)
style_device_rgblight_color_btn_1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_color_btn_1_main_main_default.set_border_width(0)
style_device_rgblight_color_btn_1_main_main_default.set_border_opa(0)
style_device_rgblight_color_btn_1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_rgblight_color_btn_1_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_rgblight_color_btn_1_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_rgblight_color_btn_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_color_btn_1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_rgblight_color_btn_1
device_rgblight_color_btn_1.add_style(style_device_rgblight_color_btn_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_color_btn_2
device_rgblight_color_btn_2 = lv.btn(device_rgblight)
device_rgblight_color_btn_2.set_pos(int(63),int(90))
device_rgblight_color_btn_2.set_size(32,32)
device_rgblight_color_btn_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_color_btn_2_main_main_default
style_device_rgblight_color_btn_2_main_main_default = lv.style_t()
style_device_rgblight_color_btn_2_main_main_default.init()
style_device_rgblight_color_btn_2_main_main_default.set_radius(30)
style_device_rgblight_color_btn_2_main_main_default.set_bg_color(lv.color_make(0xdd,0xff,0x00))
style_device_rgblight_color_btn_2_main_main_default.set_bg_grad_color(lv.color_make(0x00,0xff,0x00))
style_device_rgblight_color_btn_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_rgblight_color_btn_2_main_main_default.set_bg_opa(255)
style_device_rgblight_color_btn_2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_color_btn_2_main_main_default.set_border_width(0)
style_device_rgblight_color_btn_2_main_main_default.set_border_opa(0)
style_device_rgblight_color_btn_2_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_rgblight_color_btn_2_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_rgblight_color_btn_2_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_rgblight_color_btn_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_color_btn_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_rgblight_color_btn_2
device_rgblight_color_btn_2.add_style(style_device_rgblight_color_btn_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_color_btn_3
device_rgblight_color_btn_3 = lv.btn(device_rgblight)
device_rgblight_color_btn_3.set_pos(int(16),int(135))
device_rgblight_color_btn_3.set_size(32,32)
device_rgblight_color_btn_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_color_btn_3_main_main_default
style_device_rgblight_color_btn_3_main_main_default = lv.style_t()
style_device_rgblight_color_btn_3_main_main_default.init()
style_device_rgblight_color_btn_3_main_main_default.set_radius(30)
style_device_rgblight_color_btn_3_main_main_default.set_bg_color(lv.color_make(0x00,0xff,0xfc))
style_device_rgblight_color_btn_3_main_main_default.set_bg_grad_color(lv.color_make(0x06,0xff,0x00))
style_device_rgblight_color_btn_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_rgblight_color_btn_3_main_main_default.set_bg_opa(255)
style_device_rgblight_color_btn_3_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_color_btn_3_main_main_default.set_border_width(0)
style_device_rgblight_color_btn_3_main_main_default.set_border_opa(0)
style_device_rgblight_color_btn_3_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_rgblight_color_btn_3_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_rgblight_color_btn_3_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_rgblight_color_btn_3_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_color_btn_3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_rgblight_color_btn_3
device_rgblight_color_btn_3.add_style(style_device_rgblight_color_btn_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_color_btn_4
device_rgblight_color_btn_4 = lv.btn(device_rgblight)
device_rgblight_color_btn_4.set_pos(int(63),int(136))
device_rgblight_color_btn_4.set_size(32,32)
device_rgblight_color_btn_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_color_btn_4_main_main_default
style_device_rgblight_color_btn_4_main_main_default = lv.style_t()
style_device_rgblight_color_btn_4_main_main_default.init()
style_device_rgblight_color_btn_4_main_main_default.set_radius(30)
style_device_rgblight_color_btn_4_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_device_rgblight_color_btn_4_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_device_rgblight_color_btn_4_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_color_btn_4_main_main_default.set_bg_opa(255)
style_device_rgblight_color_btn_4_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_color_btn_4_main_main_default.set_border_width(0)
style_device_rgblight_color_btn_4_main_main_default.set_border_opa(0)
style_device_rgblight_color_btn_4_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_rgblight_color_btn_4_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_rgblight_color_btn_4_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_rgblight_color_btn_4_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_color_btn_4_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_rgblight_color_btn_4
device_rgblight_color_btn_4.add_style(style_device_rgblight_color_btn_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_round_color
device_rgblight_round_color = lv.obj(device_rgblight)
device_rgblight_round_color.set_pos(int(175),int(71))
device_rgblight_round_color.set_size(80,80)
device_rgblight_round_color.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_round_color_main_main_default
style_device_rgblight_round_color_main_main_default = lv.style_t()
style_device_rgblight_round_color_main_main_default.init()
style_device_rgblight_round_color_main_main_default.set_radius(50)
style_device_rgblight_round_color_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_round_color_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_round_color_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_round_color_main_main_default.set_bg_opa(255)
style_device_rgblight_round_color_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_round_color_main_main_default.set_border_width(0)
style_device_rgblight_round_color_main_main_default.set_border_opa(255)
style_device_rgblight_round_color_main_main_default.set_pad_left(0)
style_device_rgblight_round_color_main_main_default.set_pad_right(0)
style_device_rgblight_round_color_main_main_default.set_pad_top(0)
style_device_rgblight_round_color_main_main_default.set_pad_bottom(0)

# add style for device_rgblight_round_color
device_rgblight_round_color.add_style(style_device_rgblight_round_color_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_wc_cpicker
device_rgblight_wc_cpicker = lv.colorwheel(device_rgblight, True)
device_rgblight_wc_cpicker.set_pos(int(140),int(36))
device_rgblight_wc_cpicker.set_size(150,150)
device_rgblight_wc_cpicker.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_rgblight_wc_cpicker_main_main_default
style_device_rgblight_wc_cpicker_main_main_default = lv.style_t()
style_device_rgblight_wc_cpicker_main_main_default.init()
style_device_rgblight_wc_cpicker_main_main_default.set_arc_width(20)

# add style for device_rgblight_wc_cpicker
device_rgblight_wc_cpicker.add_style(style_device_rgblight_wc_cpicker_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_brightness_label
device_rgblight_brightness_label = lv.label(device_rgblight)
device_rgblight_brightness_label.set_pos(int(4),int(223))
device_rgblight_brightness_label.set_size(100,20)
device_rgblight_brightness_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_rgblight_brightness_label.set_text("Brightness")
device_rgblight_brightness_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_rgblight_brightness_label_main_main_default
style_device_rgblight_brightness_label_main_main_default = lv.style_t()
style_device_rgblight_brightness_label_main_main_default.init()
style_device_rgblight_brightness_label_main_main_default.set_radius(0)
style_device_rgblight_brightness_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_brightness_label_main_main_default.set_bg_opa(0)
style_device_rgblight_brightness_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_rgblight_brightness_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_rgblight_brightness_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_rgblight_brightness_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_brightness_label_main_main_default.set_text_letter_space(0)
style_device_rgblight_brightness_label_main_main_default.set_text_line_space(0)
style_device_rgblight_brightness_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_device_rgblight_brightness_label_main_main_default.set_pad_left(0)
style_device_rgblight_brightness_label_main_main_default.set_pad_right(0)
style_device_rgblight_brightness_label_main_main_default.set_pad_top(0)
style_device_rgblight_brightness_label_main_main_default.set_pad_bottom(0)

# add style for device_rgblight_brightness_label
device_rgblight_brightness_label.add_style(style_device_rgblight_brightness_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_brightness_percent_label
device_rgblight_brightness_percent_label = lv.label(device_rgblight)
device_rgblight_brightness_percent_label.set_pos(int(238),int(229))
device_rgblight_brightness_percent_label.set_size(55,20)
device_rgblight_brightness_percent_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_rgblight_brightness_percent_label.set_text("100%")
device_rgblight_brightness_percent_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_rgblight_brightness_percent_label_main_main_default
style_device_rgblight_brightness_percent_label_main_main_default = lv.style_t()
style_device_rgblight_brightness_percent_label_main_main_default.init()
style_device_rgblight_brightness_percent_label_main_main_default.set_radius(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_percent_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_percent_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_brightness_percent_label_main_main_default.set_bg_opa(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_device_rgblight_brightness_percent_label_main_main_default.set_text_font(lv.font_PingFang_Regular_16)
except AttributeError:
    try:
        style_device_rgblight_brightness_percent_label_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_device_rgblight_brightness_percent_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_rgblight_brightness_percent_label_main_main_default.set_text_letter_space(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_text_line_space(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_rgblight_brightness_percent_label_main_main_default.set_pad_left(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_pad_right(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_pad_top(0)
style_device_rgblight_brightness_percent_label_main_main_default.set_pad_bottom(0)

# add style for device_rgblight_brightness_percent_label
device_rgblight_brightness_percent_label.add_style(style_device_rgblight_brightness_percent_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create device_rgblight_brightness_slider
device_rgblight_brightness_slider = lv.slider(device_rgblight)
device_rgblight_brightness_slider.set_pos(int(25),int(249))
device_rgblight_brightness_slider.set_size(265,15)
device_rgblight_brightness_slider.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_rgblight_brightness_slider.set_range(0, 100)
device_rgblight_brightness_slider.set_value(50, False)

# create style style_device_rgblight_brightness_slider_main_main_default
style_device_rgblight_brightness_slider_main_main_default = lv.style_t()
style_device_rgblight_brightness_slider_main_main_default.init()
style_device_rgblight_brightness_slider_main_main_default.set_radius(30)
style_device_rgblight_brightness_slider_main_main_default.set_bg_color(lv.color_make(0x43,0x43,0x43))
style_device_rgblight_brightness_slider_main_main_default.set_bg_grad_color(lv.color_make(0x43,0x43,0x43))
style_device_rgblight_brightness_slider_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_brightness_slider_main_main_default.set_bg_opa(255)
style_device_rgblight_brightness_slider_main_main_default.set_outline_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_slider_main_main_default.set_outline_width(0)
style_device_rgblight_brightness_slider_main_main_default.set_outline_opa(0)

# add style for device_rgblight_brightness_slider
device_rgblight_brightness_slider.add_style(style_device_rgblight_brightness_slider_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_rgblight_brightness_slider_main_indicator_default
style_device_rgblight_brightness_slider_main_indicator_default = lv.style_t()
style_device_rgblight_brightness_slider_main_indicator_default.init()
style_device_rgblight_brightness_slider_main_indicator_default.set_radius(30)
style_device_rgblight_brightness_slider_main_indicator_default.set_bg_color(lv.color_make(0xcf,0xcf,0xcf))
style_device_rgblight_brightness_slider_main_indicator_default.set_bg_grad_color(lv.color_make(0xcf,0xcf,0xcf))
style_device_rgblight_brightness_slider_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_brightness_slider_main_indicator_default.set_bg_opa(255)

# add style for device_rgblight_brightness_slider
device_rgblight_brightness_slider.add_style(style_device_rgblight_brightness_slider_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# create style style_device_rgblight_brightness_slider_main_knob_default
style_device_rgblight_brightness_slider_main_knob_default = lv.style_t()
style_device_rgblight_brightness_slider_main_knob_default.init()
style_device_rgblight_brightness_slider_main_knob_default.set_radius(30)
style_device_rgblight_brightness_slider_main_knob_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_slider_main_knob_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_rgblight_brightness_slider_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_device_rgblight_brightness_slider_main_knob_default.set_bg_opa(255)

# add style for device_rgblight_brightness_slider
device_rgblight_brightness_slider.add_style(style_device_rgblight_brightness_slider_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)


























# content from custom.py

# Load the default screen
lv.scr_load(screen_main)

while SDL.check():
    time.sleep_ms(5)
