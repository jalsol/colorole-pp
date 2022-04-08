cmake_minimum_required(VERSION 3.6)
project(colorole)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(src)
file(GLOB_RECURSE cpp_files CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${cpp_files})

add_subdirectory(deps/sleepy-discord)
target_link_libraries(${PROJECT_NAME} sleepy-discord)