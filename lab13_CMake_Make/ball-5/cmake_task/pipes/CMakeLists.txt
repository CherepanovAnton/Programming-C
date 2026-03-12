# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.c

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/pipes/read_pipe.c
    ${PROJECT_SOURCE_DIR}/pipes/write_pipe.c)

add_library(PIPES_LIB SHARED ${SOURCES})