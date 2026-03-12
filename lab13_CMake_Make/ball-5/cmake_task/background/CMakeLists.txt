# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes

add_library(BACKGROUND_LIB SHARED ./background.c)

target_link_libraries(BACKGROUND_LIB PIPES_LIB)