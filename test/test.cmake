file(GLOB_RECURSE SOURCES "test/src/*.cpp")
file(GLOB_RECURSE HEADERS "test/src/*.h")

add_library(test SHARED ${SOURCES} ${HEADERS})

add_dependencies(test
    puzzlib
)

target_link_libraries(test
    puzzlib
)

target_include_directories(test PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib
    ${CMAKE_SOURCE_DIR}/puzzlib/src
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/spdlog/include
)

target_compile_definitions(test PRIVATE
    PUZZ_PLATFORM_WINDOWS
    USER_BUILD_DLL
)