

#GUI-Guider-1.6.1-GA


if(ESP_PLATFORM)

file(GLOB CUS_SOURCES *.c)
set(CUS_INCLUDE_DIRS .)

idf_component_register(SRCS ${CUS_SOURCES}
                       INCLUDE_DIRS ${CUS_INCLUDE_DIRS}
                       REQUIRES esp_wifi)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_LVGL_H_INCLUDE_SIMPLE")

else()
    message(FATAL_ERROR "LVGL GUI-Guider generated: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()

