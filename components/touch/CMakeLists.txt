
set(SOURCES_DIR 
	"gslx680n"
)

idf_component_register(
	SRC_DIRS ${SOURCES_DIR}
	INCLUDE_DIRS .
	PRIV_REQUIRES "driver" "i2c_bus"
)
