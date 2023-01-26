set(SOURCES
    puzzlib/src/Core/Application.cpp
)

set(HEADERS
    puzzlib/src/Core/Application.h
    puzzlib/src/Core/Core.h
    puzzlib/src/Core/EntryPoint.h
    puzzlib/puzzlib.h
)

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

target_link_libraries(puzzlib
)

target_include_directories(puzzlib PRIVATE
)

target_compile_definitions(puzzlib PRIVATE
)