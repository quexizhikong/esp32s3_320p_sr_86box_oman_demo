
#ifndef __BOARD_PIN_H__
#define __BOARD_PIN_H__

#ifdef __cplusplus
extern "C" {
#endif

//硬件1 启明320*320版本 徐总定制
//==============================================================sr_86_box_320
#if CONFIG_EXAMPLE_BOARD_1
// #define LCD_RESET_PIN 6
#define LCD_RESET_PIN -1
#define LCD_RS_PIN 01
#define LCD_CS_PIN -1
#define LCD_TE_PIN -1
#define LCD_WR_PIN 2
#define LCD_RD_PIN -1

#define LCD_D0_PIN (42)
#define LCD_D1_PIN (41)
#define LCD_D2_PIN (40)
#define LCD_D3_PIN (39)
#define LCD_D4_PIN (38)
#define LCD_D5_PIN (15)
#define LCD_D6_PIN (16)
#define LCD_D7_PIN (17)

#define LCD_WIDTH 320
#define LCD_HIGHT 320
#define LCD_BL_PIN 45

#define TOUCH_RESET_PIN 6
#define TOUCH_IIC_SDA 4
#define TOUCH_IIC_SCL 5
#define TOUCH_IIC_INT 7

#define CODEC_IIC_SDA 4
#define CODEC_IIC_SCL 5
#define CODEC_PA_PIN 12

#define BOARD_I2S_NUM      (I2S_NUM_1)
#define I2S_SCLK_PIN       (GPIO_NUM_48)
#define I2S_LRCK_PIN       (GPIO_NUM_14)
#define I2S_MCLK_PIN       (GPIO_NUM_47)
#define I2S_SDIN_PIN       (GPIO_NUM_13)
#define I2S_DOUT_PIN       (GPIO_NUM_21)

#define AL01_TX_PIN (46)
#define AL01_RX_PIN (9)
//==============================================================
#elif CONFIG_EXAMPLE_BOARD_2
//启明AR-480
#define LCD_RESET_PIN -1
#define LCD_RS_PIN 13
#define LCD_CS_PIN -1//14
#define LCD_TE_PIN -1
#define LCD_WR_PIN 12
#define LCD_RD_PIN -1

#define LCD_D0_PIN (11)
#define LCD_D1_PIN (10)
#define LCD_D2_PIN (9)
#define LCD_D3_PIN (3)
#define LCD_D4_PIN (20)
#define LCD_D5_PIN (19)
#define LCD_D6_PIN (8)
#define LCD_D7_PIN (18)

#define LCD_WIDTH 320
#define LCD_HIGHT 320
#define LCD_BL_PIN 21

// CodeC IIC
#define CODEC_IIC_SCL   	6
#define CODEC_IIC_SDA   	7
#define CODEC_PA_PIN 		-1

#define TOUCH_IIC_SCL   	6
#define TOUCH_IIC_SDA   	7
#define TOUCH_RESET_PIN   	-1
#define TOUCH_IIC_INT 		-1
// I2S
#define BOARD_I2S_NUM      (I2S_NUM_1)
#define I2S_SCLK_PIN       (GPIO_NUM_48)
#define I2S_LRCK_PIN       (GPIO_NUM_47)
#define I2S_MCLK_PIN       (GPIO_NUM_38)
#define I2S_SDIN_PIN       (GPIO_NUM_21)
#define I2S_DOUT_PIN       (GPIO_NUM_39)
//==============================================================
//金安T3W公模320*320
#elif CONFIG_EXAMPLE_BOARD_3
// #define LCD_RESET_PIN 6
#define LCD_RESET_PIN -1//和触摸共用一个复位脚 在触摸初始化当中复位
#define LCD_RS_PIN 13
#define LCD_CS_PIN 14
#define LCD_TE_PIN -1
#define LCD_WR_PIN 12
#define LCD_RD_PIN -1

#define LCD_D0_PIN (11)
#define LCD_D1_PIN (10)
#define LCD_D2_PIN (9)
#define LCD_D3_PIN (3)
#define LCD_D4_PIN (20)
#define LCD_D5_PIN (19)
#define LCD_D6_PIN (8)
#define LCD_D7_PIN (18)

#define LCD_WIDTH 320
#define LCD_HIGHT 320
#define LCD_BL_PIN 21
//金安T3W公模320*320
#define TOUCH_RESET_PIN 6
#define TOUCH_IIC_SDA 5
#define TOUCH_IIC_SCL 4
#define TOUCH_IIC_INT 7

#define CODEC_IIC_SDA 5
#define CODEC_IIC_SCL 4
#define CODEC_PA_PIN 17

#define BOARD_I2S_NUM      (I2S_NUM_1)
#define I2S_MCLK_PIN       (GPIO_NUM_42)
#define I2S_SCLK_PIN       (GPIO_NUM_41)
#define I2S_LRCK_PIN       (GPIO_NUM_48)
#define I2S_SDIN_PIN       (GPIO_NUM_47)
#define I2S_DOUT_PIN       (GPIO_NUM_40)

////启明AR-480
//// I2S
//#define BOARD_I2S_NUM      (I2S_NUM_1)
//#define I2S_SCLK_PIN       (GPIO_NUM_48)
//#define I2S_LRCK_PIN       (GPIO_NUM_47)
//#define I2S_MCLK_PIN       (GPIO_NUM_38)
//#define I2S_SDIN_PIN       (GPIO_NUM_21)
//#define I2S_DOUT_PIN       (GPIO_NUM_39)
//
//// CodeC IIC
//#define CODEC_IIC_SCL   6
//#define CODEC_IIC_SDA   7
//
//#define TOUCH_IIC_SCL   6
//#define TOUCH_IIC_SDA   7
//#define TOUCH_RESET_PIN -1
//#define TOUCH_IIC_INT -1
//#define CODEC_PA_PIN -1
//==============================================================
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*__BOARD_PIN_H__*/

