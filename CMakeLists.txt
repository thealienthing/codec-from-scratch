cmake_minimum_required(VERSION 3.10.0)
project(codec VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(${CMAKE_SOURCE_DIR}/doctest doctest)

set(CODEC_INCLUDE
    include/codec.hpp
    include/buffer.hpp
    include/huffman.hpp
)

set(CODEC_SRC
    src/codec.cpp
    src/buffer.cpp
    src/huffman.cpp
)

add_library(codec SHARED
    include
    ${CODEC_SRC}
    ${CODEC_INCLUDE}
)
target_include_directories(codec PUBLIC 
    include
)

add_executable(test main.cpp)
target_link_libraries(test codec doctest)

