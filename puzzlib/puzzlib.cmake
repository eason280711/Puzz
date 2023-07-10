file(GLOB_RECURSE SOURCES "puzzlib/src/*.cpp")
file(GLOB_RECURSE HEADERS "puzzlib/src/*.h")

file(GLOB_RECURSE TSOURCES "puzzlib/vendor/ImGuiColorTextEdit/*.h")
file(GLOB_RECURSE THEADERS "puzzlib/vendor/ImGuiColorTextEdit/*.cpp")

# should update to include CmakeLists.txt in ImGuiFileDialog
file(GLOB_RECURSE FSOURCES "puzzlib/vendor/ImGuiFileDialog/*.h")
file(GLOB_RECURSE FHEADERS "puzzlib/vendor/ImGuiFileDialog/*.cpp")

add_library(puzzlib SHARED ${SOURCES} ${HEADERS} ${TSOURCES} ${THEADERS} ${FSOURCES} ${FHEADERS})

find_package(ftxui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

find_package(Corrade REQUIRED Containers Utility)
find_package(Magnum REQUIRED 
    GL 
    Shaders 
    MeshTools
    Primitives
    SceneGraph
    Trade)

find_package(imgui REQUIRED)
find_package(box2d CONFIG REQUIRED)

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
    Corrade::Containers Corrade::Utility
    ftxui::dom ftxui::screen ftxui::component
    glfw
    Magnum::GL
    Magnum::GLContext
    Magnum::Magnum
    Magnum::Shaders
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Trade
    imgui::imgui
    box2d::box2d
)

target_include_directories(puzzlib PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib/src
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/ImGuiColorTextEdit
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/ImGuiFileDialog
    ${PDC_INCLUDES}
)

target_compile_definitions(puzzlib PRIVATE
    PUZZ_PLATFORM_WINDOWS
    PUZZ_BUILD_DLL
)