cmake_minimum_required(VERSION 3.21)

project(Puzz
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(puzzlib/puzzlib.cmake)
include(application/application.cmake)