
file(GLOB EXTERN_FILES resource/*)

idf_component_register(
    SRC_DIRS "." "app" "board" "board/codec" 
    INCLUDE_DIRS "." "app" "board" "board/codec" 
    EMBED_FILES ${EXTERN_FILES}
)


target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-error=stringop-truncation")
#target_compile_definitions(${COMPONENT_LIB} PUBLIC -Wno-error=stringop-truncation)
# target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_CONF_INCLUDE_SIMPLE=1)

# Create a SPIFFS image from the contents of the 'spiffs_image' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash'.
spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
