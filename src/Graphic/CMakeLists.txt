cmake_minimum_required(VERSION 3.13)

target_sources(map_generator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Graphic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp"
)
