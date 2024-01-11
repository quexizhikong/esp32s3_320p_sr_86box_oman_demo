

#GUI-Guider-1.6.1-GA


if(ESP_PLATFORM)

file(GLOB_RECURSE GEN_SOURCES *.c  guider_fonts/* images/*.c)
set(GEN_INCLUDE_DIRS . guider_customer_fonts guider_fonts images)

idf_component_register(SRCS ${GEN_SOURCES}
                       INCLUDE_DIRS ${GEN_INCLUDE_DIRS}
                       REQUIRES lvgl json custom)

else()
    message(FATAL_ERROR "LVGL GUI-Guider generated: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()
