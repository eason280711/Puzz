set(SOURCES
    puzzlib/puzz.cpp
)

set(HEADERS
)

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

target_link_libraries(puzzlib
)

target_include_directories(puzzlib PRIVATE
)

target_compile_definitions(puzzlib PRIVATE
)