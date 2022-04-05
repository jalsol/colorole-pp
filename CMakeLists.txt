cmake_minimum_required(VERSION 3.10)
project(colorole)

# Settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Source files
include_directories(./src)
file(GLOB_RECURSE cpp_files CONFIGURE_DEPENDS "src/*.cpp")

# Executable
add_executable(${PROJECT_NAME} ${cpp_files})

# Dependencies
add_subdirectory(deps/sleepy-discord)
target_link_libraries(${PROJECT_NAME} sleepy-discord)
