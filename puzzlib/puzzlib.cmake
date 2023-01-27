set(SOURCES
    puzzlib/src/Core/Application.cpp
)

set(HEADERS
    puzzlib/src/Core/Application.h
    puzzlib/src/Core/Core.h
    puzzlib/src/Core/EntryPoint.h
    puzzlib/src/Core/cnt_ptr.h
    puzzlib/src/Core/Inherit.h
    puzzlib/src/Core/Object.h
    puzzlib/src/Containers/Array.h
    puzzlib/src/State/State.h
    puzzlib/puzzlib.h
)

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

target_link_libraries(puzzlib
)

target_include_directories(puzzlib PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib/src
)

target_compile_definitions(puzzlib PRIVATE
)