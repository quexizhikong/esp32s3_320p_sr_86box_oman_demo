/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#define DEFAULT_FD_NUM      2
#define DEFAULT_MOUNT_POINT "/spiffs"

static const char *TAG = "bsp_spiffs";

esp_err_t bsp_spiffs_init(char *partition_label, char *mount_point, size_t max_files)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = mount_point,
        .partition_label = partition_label,
        .max_files = max_files,
        .format_if_mount_failed = false,
    };

//    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);
//
//    if (ESP_OK != ret_val) {
//        return ret_val;
//    }
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);

    if (ret_val != ESP_OK) {
        if (ret_val == ESP_FAIL) {
            printf("Failed to mount or format filesystem\n");
        } else if (ret_val == ESP_ERR_NOT_FOUND) {
            printf("Failed to find SPIFFS partition\n");
        } else {
            printf("Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret_val));
        }
        return ESP_FAIL;
    }

    size_t total = 0, used = 0;
    ret_val = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret_val != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret_val));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return ret_val;
}

esp_err_t bsp_spiffs_init_default(void)
{
    return bsp_spiffs_init(NULL, DEFAULT_MOUNT_POINT, DEFAULT_FD_NUM);
}

esp_err_t bsp_spiffs_deinit(char *partition_label)
{
    return esp_vfs_spiffs_unregister(partition_label);
}

esp_err_t bsp_spiffs_deinit_default(void)
{
    return bsp_spiffs_deinit(NULL);
}
