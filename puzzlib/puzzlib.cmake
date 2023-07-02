file(GLOB_RECURSE SOURCES "puzzlib/src/*.cpp")
file(GLOB_RECURSE HEADERS "puzzlib/src/*.h")

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

find_path(PDC_INCLUDES curses.h)
find_library(PDC_LIBS pdcurses REQUIRED)

find_package(ftxui CONFIG REQUIRED)

target_link_libraries(puzzlib
    ${PDC_LIBS}
    ftxui::dom ftxui::screen ftxui::component
)

target_include_directories(puzzlib PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib/src
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/spdlog/include
    ${PDC_INCLUDES}
)

target_compile_definitions(puzzlib PRIVATE
    PUZZ_PLATFORM_WINDOWS
    PUZZ_BUILD_DLL
)