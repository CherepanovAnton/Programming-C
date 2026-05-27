cmake_minimum_required(VERSION 3.28.3)

project(tests)

enable_testing()

add_library(factorial factorial.c)

add_executable(tests tests.c)

target_link_libraries(tests factorial)

add_test(NAME DefaulUse COMMAND tests DefaultUse)
add_test(NAME NegativeDgt COMMAND tests NegativeDgt)
add_test(NAME Overflow COMMAND tests Overflow)