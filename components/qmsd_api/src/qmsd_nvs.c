
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_timer.h"
#include <errno.h>
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "qmsd_api.h"


#define QMSD_STORAGE_PARTITION 	"qmsd_storage"

static SemaphoreHandle_t g_qmsd_nvs_sem = NULL;

static const char *TAG = "qmsd_storage";



/**
 * @brief Init NVS storage the project from qmsd has called this function so you don't have to call again in apps
 * 
 */
void qmsd_nvs_init(void)
{
    esp_err_t err = nvs_flash_init_partition(QMSD_STORAGE_PARTITION);
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    	ESP_LOGE(TAG,"nvs_flash_erase %s",QMSD_STORAGE_PARTITION);

        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init_partition(QMSD_STORAGE_PARTITION);
    }
    ESP_ERROR_CHECK(err);

	printf("%s init suss",QMSD_STORAGE_PARTITION);

    g_qmsd_nvs_sem = xSemaphoreCreateMutex();

    if(g_qmsd_nvs_sem)
    {
    	printf("%s create Mutex suss",QMSD_STORAGE_PARTITION);
    }
}

esp_err_t qmsd_nvs_set_blob(const char *name, const char *key, void *data, size_t length)
{
    nvs_handle handle;
    esp_err_t res = ESP_FAIL;
    if (g_qmsd_nvs_sem)
    {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY))
        {
			res = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &handle);
			if (res != ESP_OK)
			{
				ESP_LOGE(TAG, "nvs open fail %s", esp_err_to_name(res));

				xSemaphoreGive(g_qmsd_nvs_sem);
				return res;
			}

			res = nvs_set_blob(handle, key, data, length);
			if (res != ESP_OK)
			{
				ESP_LOGE(TAG, "nvs set blob fail %s", esp_err_to_name(res));

				xSemaphoreGive(g_qmsd_nvs_sem);
				return res;
			}

			res = nvs_commit(handle);
			if (res != ESP_OK)
			{
				ESP_LOGE(TAG, "nvs commit fail %s", esp_err_to_name(res));

				xSemaphoreGive(g_qmsd_nvs_sem);
				return res;
			}

			nvs_close(handle);
		    xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return res;
}

esp_err_t qmsd_nvs_get_blob(const char *name, const char *key, void *data, size_t length)
{
    nvs_handle handle;
    esp_err_t res = ESP_FAIL;
    if (g_qmsd_nvs_sem)
    {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY))
        {
			res = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READONLY, &handle);
			if (res != ESP_OK)
			{
				ESP_LOGE(TAG, "nvs open fail %s", esp_err_to_name(res));

				xSemaphoreGive(g_qmsd_nvs_sem);
				return res;
			}

			res = nvs_get_blob(handle, key, data, &length);
			if (res != ESP_OK)
			{
				ESP_LOGW(TAG, "size %d", length);
				ESP_LOGW(TAG, "nvs get blob fail %s", esp_err_to_name(res));

				xSemaphoreGive(g_qmsd_nvs_sem);
				return res;
			}

//			res = nvs_commit(handle);
//			if (res != ESP_OK)
//			{
//				ESP_LOGE(TAG, "nvs commit fail %s", esp_err_to_name(res));
//
//				xSemaphoreGive(g_qmsd_nvs_sem);
//				return res;
//			}

			nvs_close(handle);
			xSemaphoreGive(g_qmsd_nvs_sem);
		}
	}

    return res;
}

/**
 * @brief Get an unsigned char in NVS flash
 * 
 * @param name Namespace of the value to read
 * @param key Key of the value to be read
 * @return uint8_t return the value in nvs with a default 0
 */
esp_err_t qmsd_nvs_get_u8(const char *name, const char *key, uint8_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READONLY, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                uint8_t u8_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_u8(my_handle, key, &u8_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = u8_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an uint8 value in NVS
 * 
 * @param name Namespace of the value to read
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_u8(const char *name, const char* key, uint8_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_u8(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }
                nvs_close(my_handle);
            }

            xSemaphoreGive(g_qmsd_nvs_sem);
            return err;
        }
    }

    return err;
}

/**
 * @brief Read an int8 value from NVS
 * 
 * @param key Key of the value to be read
 * @return int8_t 
 */
esp_err_t qmsd_nvs_get_i8(const char *name, const char *key, int8_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return 0;
            } else {
                int8_t i8_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_i8(my_handle, key, &i8_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = i8_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an int8 value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_i8(const char *name, const char* key,int8_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_i8(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

/**
 * @brief Read an int8 value from NVS
 * 
 * @param key Key of the value to be read
 * @return int8_t 
 */
esp_err_t qmsd_nvs_get_u16(const char *name, const char *key, uint16_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                uint16_t tmp_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_u16(my_handle, key, &tmp_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = tmp_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an int8 value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_u16(const char *name, const char* key,uint16_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_u16(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

/**
 * @brief Read an int16 value from NVS
 * 
 * @param key Key of the value to be read
 * @return int8_t 
 */
esp_err_t qmsd_nvs_get_i16(const char *name, const char *key, int16_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                int16_t tmp_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_i16(my_handle, key, &tmp_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = tmp_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an int16 value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_i16(const char *name, const char* key,int16_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_i16(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

/**
 * @brief 
 * 
 * @param key Key of the value to be read in read function
 * @return uint32_t 
 */
esp_err_t qmsd_nvs_get_u32(const char*name, const char* key, uint32_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                uint32_t i32_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_u32(my_handle, key, &i32_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = i32_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an unsigned int value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_u32(const char*name, const char* key, uint32_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_u32(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                       ESP_LOGE(TAG,"write suss!");
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_get_i32(const char*name, const char* key, int32_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                int32_t i32_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_i32(my_handle, key, &i32_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = i32_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an int value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_i32(const char*name, const char* key,int32_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_i32(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

/**
 * @brief 
 * 
 * @param key Key of the value to be read in read function
 * @return uint32_t 
 */
esp_err_t qmsd_nvs_get_u64(const char*name, const char* key, uint64_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                uint64_t tmp_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_u64(my_handle, key, &tmp_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = tmp_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an unsigned int value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_u64(const char*name, const char* key, uint64_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_u64(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_get_i64(const char*name, const char* key, int64_t *value)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                int64_t tmp_res = 0; // value will default to 0, if not set yet in NVS
                err = nvs_get_i64(my_handle, key, &tmp_res);
                switch (err) {
                    case ESP_OK:
                        break;
                    case ESP_ERR_NVS_NOT_FOUND:
                       ESP_LOGE(TAG,"The value is not initialized yet!");
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                }
                *value = tmp_res;
                nvs_close(my_handle);
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an int64 value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_i64(const char*name, const char* key, int64_t input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_i64(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }

                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_get_str_size(const char*name, const char* key, size_t *str_size)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                size_t tmp_size;
                err = nvs_get_str(my_handle, key, NULL, &tmp_size);
                nvs_close(my_handle);
                if (err == ESP_OK) {
                    *str_size = tmp_size;
                } else {
                    *str_size = 0;
                }
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }   
        }
    }

    return err;
}
esp_err_t qmsd_nvs_get_blob_size(const char*name, const char* key, size_t *blob_size)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                size_t tmp_size;
                err = nvs_get_blob(my_handle, key, NULL, &tmp_size);
                nvs_close(my_handle);
                if (err == ESP_OK) {
                    *blob_size = tmp_size;
                } else {
                    *blob_size = 0;
                }
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

esp_err_t qmsd_nvs_get_str(const char*name, const char* key,char *output, size_t size)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_get_str(my_handle, key, output, &size);
                nvs_close(my_handle);

               ESP_LOGE(TAG,"read suss!");
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            }
        }
    }

    return err;
}

/**
 * @brief Storage an unsigned int value in NVS
 * 
 * @param key Key of the value to be read in read function
 * @param input Value of the key
 * @return esp_err_t Error number
 */
esp_err_t qmsd_nvs_set_str(const char*name, const char* key,char* input)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
            	ESP_LOGW(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_set_str(my_handle, key,input);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        ESP_LOGI(TAG,"save suss!");
                        break;
                    default :
                    	ESP_LOGW(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }
                nvs_close(my_handle);  
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_clear_key(const char*name, const char* key)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
            	ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_erase_key(my_handle, key);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                    	ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }
                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_find_key(const char*name, const char* key)
{
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem)
    {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY))
        {
			//nvs_entry_find(const char *part_name, const char *name_name, nvs_type_t type)
			nvs_iterator_t it = nvs_entry_find(QMSD_STORAGE_PARTITION, name, NVS_TYPE_ANY);//任意类型
			while (it != NULL)
			{
				nvs_entry_info_t info;
				nvs_entry_info(it, &info);
				//ESP_LOGI(TAG,"find key->%s",info.key);

				if(strcmp(info.key,key)==0)
				{//存在 退出
					//ESP_LOGI(TAG,"key->%s is exists and match suss",info.key);
					xSemaphoreGive(g_qmsd_nvs_sem);
					return ESP_OK;
				}
				else
				{
					//ESP_LOGI(TAG,"key->%s is not exists",info.key);
				}

				//不存在继续遍历
				it = nvs_entry_next(it);
			}

            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}
esp_err_t qmsd_nvs_print_find_key(const char*name)
{
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem)
    {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY))
        {
			//nvs_entry_find(const char *part_name, const char *name_name, nvs_type_t type)
			nvs_iterator_t it = nvs_entry_find(QMSD_STORAGE_PARTITION, name, NVS_TYPE_ANY);//任意类型
			while (it != NULL)
			{
				nvs_entry_info_t info;
				nvs_entry_info(it, &info);
				ESP_LOGI(TAG,"\nnamespace->%s,key->%s",name,info.key);

				//不存在继续遍历
				it = nvs_entry_next(it);
			}

            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}
esp_err_t qmsd_nvs_clear_namespace(const char*name)
{
    nvs_handle_t my_handle;
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_open_from_partition(QMSD_STORAGE_PARTITION, name, NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
               ESP_LOGE(TAG,"Error (%s) opening NVS handle!", esp_err_to_name(err));
                xSemaphoreGive(g_qmsd_nvs_sem);
                return err;
            } else {
                err = nvs_erase_all(my_handle);
                switch (err) {
                    case ESP_OK:
                        err = nvs_commit(my_handle);
                        break;
                    default :
                       ESP_LOGE(TAG,"Error (%s) reading!", esp_err_to_name(err));
                        return err;
                }
                nvs_close(my_handle);
            }
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}

esp_err_t qmsd_nvs_clear_all(void)
{
    esp_err_t err = ESP_FAIL;

    if (g_qmsd_nvs_sem) {
        if (pdTRUE == xSemaphoreTake(g_qmsd_nvs_sem, portMAX_DELAY)) {
            err = nvs_flash_erase_partition(QMSD_STORAGE_PARTITION);
            xSemaphoreGive(g_qmsd_nvs_sem);
        }
    }

    return err;
}
