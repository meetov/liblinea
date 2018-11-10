cmake_minimum_required(VERSION 3.0)

project( List LANGUAGES C )

set( List_VERSION_MAJOR 1 )
set( List_VERSION_MINOR 0 )

# configure_file (
# 	"${PROJECT_SOURCE_DIR}/include/liblist.h"

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra" )
# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror" )

add_library( list SHARED 
	"${PROJECT_SOURCE_DIR}/src/liblist.c"
)

target_include_directories( list PUBLIC ${PROJECT_SOURCE_DIR}/include )