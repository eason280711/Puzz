file(GLOB_RECURSE SOURCES "puzzlib/src/*.cpp")
file(GLOB_RECURSE HEADERS "puzzlib/src/*.h")

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

find_package(ftxui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED GL Shaders)
find_package(imgui REQUIRED)

if(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED CglContext)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED GlxContext)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WglContext)
else()
    message(FATAL_ERROR "No context handler available on this platform")
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

target_link_libraries(puzzlib PRIVATE
    ftxui::dom ftxui::screen ftxui::component
    glfw
    Magnum::GL
    Magnum::GLContext
    Magnum::Magnum
    Magnum::Shaders
    imgui::imgui
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