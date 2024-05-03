file(GLOB_RECURSE SOURCES "puzzlib/src/*.cpp")

file(GLOB_RECURSE HEADERS "puzzlib/src/*.h")

add_library(puzzlib STATIC ${SOURCES} ${HEADERS})

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)
find_package(GLEW REQUIRED)
find_package(soil2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(puzzlib
    glfw   
    spdlog::spdlog
    spdlog::spdlog_header_only
    imgui::imgui
    glm::glm
    OpenGL::GL
    GLEW::GLEW
    soil2
)

target_include_directories(puzzlib PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib/src
)

target_compile_definitions(puzzlib PRIVATE
)