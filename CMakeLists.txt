cmake_minimum_required(VERSION 3.22)
project(colorole)

# Settings
# set(CMAKE_WARN_DEPRECATED FALSE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Add DPP as dependency
add_subdirectory(libs/DPP)
# add_subdirectory(libs/spdlog)

# Source files
include_directories(src)
file(GLOB_RECURSE cpp_files CONFIGURE_DEPENDS "src/*.cpp")

# Executable
add_executable(${PROJECT_NAME} ${cpp_files})

# Linking libraries
target_link_libraries(${PROJECT_NAME}
    dpp
    # spdlog
)

# Specify includes
target_include_directories(${PROJECT_NAME} PRIVATE
    libs/DPP/include
    # libs/spdlog/include
)