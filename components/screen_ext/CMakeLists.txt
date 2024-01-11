set(srcs "src/esp_lcd_panel_gs_st7796.c")
set(includes "include" )
set(priv_requires "driver" "esp_lcd")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       PRIV_REQUIRES ${priv_requires})
