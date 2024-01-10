cmake_minimum_required(VERSION 3.18)
project(map_generator
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory(src)

