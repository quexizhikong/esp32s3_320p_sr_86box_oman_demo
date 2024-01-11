#pragma once

#include "stdint.h"

#define QMSD_ERROR_CHECK(con, err, format, ...) do { \
        if (con) { \
            if(*format != '\0') \
                ESP_LOGW(TAG, "<%s> " format, esp_err_to_name(err), ##__VA_ARGS__); \
            return err; \
        } \
    } while(0)

#define QMSD_ERROR_ASSERT(err) do { \
        esp_err_t __err_rc = (err); \
        if (__err_rc != ESP_OK) { \
            ESP_LOGW(TAG, "<%s> QMSD_ERROR_ASSERT failed, at 0x%08x, expression: %s", \
                     esp_err_to_name(__err_rc), (intptr_t)__builtin_return_address(0) - 3, __ASSERT_FUNC); \
            assert(0 && #err); \
        } \
    } while(0)

#define QMSD_ERROR_GOTO(con, lable, format, ...) do { \
        if (con) { \
            if(*format != '\0') \
                ESP_LOGW(TAG, format, ##__VA_ARGS__); \
            goto lable; \
        } \
    } while(0)

#define QMSD_ERROR_CONTINUE(con, format, ...) { \
        if (con) { \
            if(*format != '\0') \
                ESP_LOGW(TAG, format, ##__VA_ARGS__); \
            continue; \
        } \
    }

#define QMSD_ERROR_BREAK(con, format, ...) { \
        if (con) { \
            if(*format != '\0') \
                ESP_LOGW(TAG, format, ##__VA_ARGS__); \
            break; \
        } \
    }

#define QMSD_PARAM_CHECK(con) do { \
        if (!(con)) { \
            ESP_LOGE(TAG, "<QMSD_ERR_INVALID_ARG> !(%s)", #con); \
            return ESP_ERR_INVALID_ARG; \
        } \
    } while(0)

#define EMBED_FILES_DECLARE(file_name) \
extern uint8_t _binary_##file_name##_start; \
extern uint8_t _binary_##file_name##_end; \
const uint8_t* _##file_name##_ptr = &_binary_##file_name##_start; \
uint32_t _##file_name##_size = (uint32_t)&_binary_##file_name##_end - (uint32_t)&_binary_##file_name##_start

// base <sys/time.h>
uint64_t qmsd_get_time_ms();

// base <sys/time.h>
uint32_t qmsd_get_time_sec();

void qmsd_debug_task_print(uint32_t interval_time);

void qmsd_debug_heap_print(uint32_t caps, uint32_t interval_time);

uint16_t crc16tablefast(uint8_t *data, uint32_t len);

uint16_t crc16tablefast_muti(uint8_t *data, uint32_t len, uint8_t *data1, uint32_t len1);
