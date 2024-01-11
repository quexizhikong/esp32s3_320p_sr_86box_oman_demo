#include "user_board.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "screen_driver.h"
#include "esp_log.h"

audio_hal_func_t* audio_hal;
static int16_t blk_init = false;
extern audio_hal_func_t AUDIO_CODEC_ZX_ES8388_DEFAULT_HANDLE;

#define ADC_I2S_CHANNEL 2

void board_backlight_init(int16_t blk_pin) {
    if (blk_pin < 0) {
        return ;
    }
    blk_init = true;
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = BOARD_LEDC_MODE,
        .timer_num        = BOARD_LEDC_TIMER,
        .duty_resolution  = BOARD_LEDC_DUTY_RES,
        .freq_hz          = BOARD_LEDC_FREQUENCY,  // Set output frequency at 1 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = BOARD_LEDC_MODE,
        .channel        = BOARD_LEDC_CHANNEL,
        .timer_sel      = BOARD_LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = blk_pin,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void qmsd_backlight_control(uint8_t light) {
    if (blk_init == false) {
        return ;
    }

    if (light > 100) {
        light = 100;
    }
    uint16_t duty = 1024.0 / 100.0 * light;
    ledc_set_duty(BOARD_LEDC_MODE, BOARD_LEDC_CHANNEL, duty);
    ledc_update_duty(BOARD_LEDC_MODE, BOARD_LEDC_CHANNEL);
}

esp_err_t board_get_feed_data(int16_t *buffer, int chunksize) {
    esp_err_t ret = ESP_OK;
    size_t bytes_read;
    ret = i2s_read(BOARD_I2S_NUM, buffer, chunksize * ADC_I2S_CHANNEL * sizeof(int16_t), &bytes_read, portMAX_DELAY);
    for (int i = chunksize - 1; i >= 0; i--) {
        buffer[i * 3 + 2] = 0;
        buffer[i * 3 + 1] = buffer[i * 2 + 1];
        buffer[i * 3 + 0] = buffer[i * 2 + 0];
    }
    return ret;
}

#define AUDIO_CODEC_DEFAULT_CONFIG() {                   \
        .adc_input  = AUDIO_HAL_ADC_INPUT_DIFFERENCE,   \
        .dac_output = AUDIO_HAL_DAC_OUTPUT_LINE1,       \
        .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,        \
        .i2s_iface = {                                  \
            .mode = AUDIO_HAL_MODE_SLAVE,               \
            .fmt = AUDIO_HAL_I2S_NORMAL,                \
            .samples = CODEC_ADC_SAMPLE_RATE,           \
            .bits = AUDIO_HAL_BIT_LENGTH_16BITS,        \
        },                                              \
};

esp_err_t board_codec_init() {
    esp_err_t ret = 0;
    audio_hal = &AUDIO_CODEC_ZX_ES8388_DEFAULT_HANDLE;
    audio_hal_codec_config_t audio_codec_cfg = AUDIO_CODEC_DEFAULT_CONFIG();
    ret = audio_hal->audio_codec_initialize(&audio_codec_cfg);
    ret |= audio_hal->audio_codec_config_iface(audio_codec_cfg.codec_mode, &audio_codec_cfg.i2s_iface);
    ret |= audio_hal->audio_codec_set_volume(100);
    audio_hal->handle = audio_hal;
    return ret;
}

#define I2S_CONFIG_DEFAULT() { \
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),      \
    .sample_rate = CODEC_ADC_SAMPLE_RATE,                                   \
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,                           \
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           \
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,                      \
    .intr_alloc_flags = ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_SHARED, \
    .dma_buf_count = 3,                                                     \
    .dma_buf_len = 160,                                                     \
    .use_apll = true,                                                       \
    .tx_desc_auto_clear = true,                                             \
    .fixed_mclk = 0                                                         \
}

esp_err_t board_i2s_init() {
    esp_err_t ret_val = ESP_OK;
    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCLK_PIN,
        .ws_io_num = I2S_LRCK_PIN,
        .data_out_num = I2S_DOUT_PIN,
        .data_in_num = I2S_SDIN_PIN,
        .mck_io_num = I2S_MCLK_PIN,
    };
    i2s_config_t i2s_config = I2S_CONFIG_DEFAULT();
    i2s_config.sample_rate = CODEC_ADC_SAMPLE_RATE;
    i2s_config.bits_per_sample = CODEC_ADC_BITS_PER_SAMPLE;
    i2s_config.use_apll = false;
    ret_val |= i2s_driver_install(BOARD_I2S_NUM, &i2s_config, 0, NULL);
    ret_val |= i2s_set_pin(BOARD_I2S_NUM, &pin_config);
    ret_val |= i2s_zero_dma_buffer(BOARD_I2S_NUM);
    return ret_val;
}

int board_get_feed_channel(void) {
    return ADC_I2S_CHANNEL;
}

void qmsd_board_hw_init() {
    board_backlight_init(LCD_BL_PIN);

#if(CODEC_PA_PIN>=0)
    gpio_config_t codec_gpio_config = {
        .pin_bit_mask = BIT64(I2S_MCLK_PIN) | BIT64(I2S_LRCK_PIN) | BIT64(I2S_SCLK_PIN) | BIT64(CODEC_PA_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&codec_gpio_config);
    gpio_set_level(I2S_MCLK_PIN, 0);
    gpio_set_level(I2S_LRCK_PIN, 0);
    gpio_set_level(I2S_SCLK_PIN, 0);
    gpio_set_level(CODEC_PA_PIN, 0);
#else
    gpio_config_t codec_gpio_config = {
        .pin_bit_mask = BIT64(I2S_MCLK_PIN) | BIT64(I2S_LRCK_PIN) | BIT64(I2S_SCLK_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&codec_gpio_config);
    gpio_set_level(I2S_MCLK_PIN, 0);
    gpio_set_level(I2S_LRCK_PIN, 0);
    gpio_set_level(I2S_SCLK_PIN, 0);
#endif

    vTaskDelay(pdMS_TO_TICKS(5));
    board_codec_init();
    vTaskDelay(pdMS_TO_TICKS(100));
    board_i2s_init();
    vTaskDelay(pdMS_TO_TICKS(100));
}
