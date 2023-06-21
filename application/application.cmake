set(SOURCES
    application/src/Application.cpp
)

set(HEADERS
)

add_executable(application ${SOURCES} ${HEADERS})

add_dependencies(application
    puzzlib
)

target_link_libraries(application
    puzzlib
)

target_include_directories(application PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib
    ${CMAKE_SOURCE_DIR}/puzzlib/src
)

target_compile_definitions(application PRIVATE
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT application)