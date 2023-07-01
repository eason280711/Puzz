cmake_minimum_required(VERSION 3.21)

project(Puzz
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(ROOT ON)
configure_file(${CMAKE_SOURCE_DIR}/cmake/Config.h.cmake ${CMAKE_SOURCE_DIR}/puzzlib/src/Config/Config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(puzzlib/puzzlib.cmake)
include(editor/editor.cmake)
include(application/application.cmake)