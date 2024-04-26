cmake_minimum_required(VERSION 3.26)

project(example1)

FILE(GLOB_RECURSE ALL_CPP_SRCS ${PROJECT_SOURCE_DIR}/*.cpp)
FILE(GLOB_RECURSE ALL_HEADER_SRCS ${PROJECT_SOURCE_DIR}/*.h)
include_directories(./) 
add_executable(example1 ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS})
target_link_libraries (example1 ion-core tlsf Dbghelp)

target_compile_features(example1 PRIVATE cxx_std_20)
if(MSVC)
	target_compile_options(example1 PRIVATE "/MP")
endif()

set_target_properties(example1 PROPERTIES FOLDER "Samples")






