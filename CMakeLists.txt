cmake_minimum_required(VERSION 3.9)
project(ftt_benchmark)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS
    src/headers/*.hpp
)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(ftt_benchmark ${SOURCES} ${HEADERS})

