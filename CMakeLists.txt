cmake_minimum_required(VERSION 3.0)

project( Liblinea LANGUAGES C )

include(CTest)

set( List_VERSION_MAJOR 1 )
set( List_VERSION_MINOR 0 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11" )

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.c")
add_library( linea SHARED 
	"${SOURCE_FILES}"
)

target_include_directories( linea PUBLIC ${PROJECT_SOURCE_DIR}/include )

if (BUILD_TESTING)
	enable_testing()
	add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()
