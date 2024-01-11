file(GLOB SOURCES *.c src/*.c)
idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "include"
                       REQUIRES  nvs_flash)
