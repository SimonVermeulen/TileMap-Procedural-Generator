cmake_minimum_required(VERSION 3.13)

target_sources(map_generator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Vector2I.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/getRandom.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/getIndexSet.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/getWeightedRandom.cpp"
)
