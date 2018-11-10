cmake_minimum_required(VERSION 3.0)

project( List LANGUAGES C )

include(CTest)

set( List_VERSION_MAJOR 1 )
set( List_VERSION_MINOR 0 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra" )

add_library( list SHARED 
	"${PROJECT_SOURCE_DIR}/src/liblist.c"
)

target_include_directories( list PUBLIC ${PROJECT_SOURCE_DIR}/include )

if (BUILD_TESTING)
	enable_testing()
	add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()