cmake_minimum_required(VERSION 3.20)
project(UNOPlusPlus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Fetch SFML from git and build for any system
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(SFML)

# Create the executable
# List source files here (cpp, c)
add_executable(UNOPlusPlus
        main.cpp
        Menu.cpp
        Player.cpp
        Game.cpp
        TestClass.hpp
)

target_link_libraries(UNOPlusPlus
        sfml-system # Required
        sfml-window # Required
        sfml-graphics # Required
)

# Set assets path for use in project
set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets")
target_compile_definitions(UNOPlusPlus PRIVATE ASSETS_PATH="${ASSETS_PATH}")