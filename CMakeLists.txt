cmake_minimum_required(VERSION 3.10.0)
project(codec VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17) # Required by magic_enum
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(MAGIC_ENUM_INCLUDE_DIR magic_enum/include)

set(CODEC_INCLUDE
    include/codec.hpp
    include/buffer.hpp
    include/huffman.hpp
    include/frame.hpp
)

set(CODEC_SRC
    src/codec.cpp
    src/buffer.cpp
    src/huffman.cpp
    src/frame.cpp
)


add_library(codec SHARED
    include
    ${CODEC_SRC}
    ${CODEC_INCLUDE}
)
target_include_directories(codec PUBLIC
    include
    ${MAGIC_ENUM_INCLUDE_DIR}
)

target_link_libraries(codec PRIVATE spdlog::spdlog)

add_executable(test tests.cpp)
target_link_libraries(test
    codec
    spdlog::spdlog
    fmt::fmt
)

add_executable(main main.cpp)
target_link_libraries(main
    codec
    spdlog::spdlog
    fmt::fmt
)