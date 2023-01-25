cmake_minimum_required(VERSION 3.21)

project(Puzz
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/Source.cpp
)

set(HEADERS
)

add_executable(Puzz ${SOURCES} ${HEADERS})