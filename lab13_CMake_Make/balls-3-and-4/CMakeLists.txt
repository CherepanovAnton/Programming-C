cmake_minimum_required(VERSION 3.28.3)

project(main)

include_directories(include)

option(SHARED "build dynamic library" OFF)
if (${SHARED})
    add_library(UTIL_LIB SHARED src/FuncLab12.c )
else()
    add_library(UTIL_LIB STATIC src/FuncLab12.c )
endif()

set(TARGET main)

set(SOURCES src/main.c)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} UTIL_LIB)