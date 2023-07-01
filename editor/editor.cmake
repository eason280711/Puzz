file(GLOB_RECURSE SOURCES "editor/src/*.cpp")
file(GLOB_RECURSE HEADERS "editor/src/*.h")

add_library(editor SHARED ${SOURCES} ${HEADERS})

add_dependencies(editor
    puzzlib
)

target_link_libraries(editor
    puzzlib
)

target_include_directories(editor PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib
    ${CMAKE_SOURCE_DIR}/puzzlib/src
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/spdlog/include
)

target_compile_definitions(editor PRIVATE
)