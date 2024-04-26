cmake_minimum_required(VERSION 3.26)

project(ion-codegen)


# Disable Strict API for release
add_compile_options(
	"$<$<CONFIG:RELEASE>:-DION_API_STRICT=0>"
	"$<$<CONFIG:RELWITHDEBINFO>:-DION_API_STRICT=0>"
	"$<$<CONFIG:MINSIZEREL>:-DION_API_STRICT=0>"
)

# Disable dev tools for release
add_compile_options(
	"$<$<CONFIG:RELEASE>:-DION_CONFIG_DEV_TOOLS=0>"
	"$<$<CONFIG:RELWITHDEBINFO>:-DION_CONFIG_DEV_TOOLS=0>"
	"$<$<CONFIG:MINSIZEREL>:-DION_CONFIG_DEV_TOOLS=0>"
)

add_compile_options(
	"$<$<CONFIG:RELEASE>:-DION_CONFIG_ERROR_CHECKING=0>"
    "$<$<CONFIG:DEBUG>:-DION_DEBUG_LOG_ENABLED=0>"
)


set( ION_ROOT_DIR ${PROJECT_SOURCE_DIR}/depend/ion-core/src)
set( ION_EXT_DIR ${PROJECT_SOURCE_DIR}/depend/ion-core/depend)

FILE(GLOB_RECURSE ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/src/*.h)
include_directories( 
	${ION_ROOT_DIR}
	${ION_EXT_DIR}
	src
	)
add_executable(ion-codegen ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS})

target_link_libraries (ion-codegen ion-core tlsf Dbghelp)

target_compile_features(ion-codegen PRIVATE cxx_std_20)
if(MSVC)
	target_compile_options(ion-codegen PRIVATE "/MP")
endif()

set_target_properties(ion-codegen PROPERTIES FOLDER "Tools")

add_subdirectory(samples)
add_subdirectory(depend)
