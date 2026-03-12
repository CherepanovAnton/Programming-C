#[[
Здесь ваша реализация
]]

cmake_minimum_required(VERSION 3.28.3)

project(main)

include_directories(pipes background)

add_subdirectory(pipes)
add_subdirectory(background)

add_executable(main src/main.c)

target_link_libraries(main BACKGROUND_LIB)

