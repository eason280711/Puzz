set(SOURCES
    puzzlib/src/Core/Application.cpp
    puzzlib/src/State/State.cpp
)

set(HEADERS
    puzzlib/src/Core/Application.h
    puzzlib/src/Core/Core.h
    puzzlib/src/Core/EntryPoint.h
    puzzlib/src/Core/ref_ptr.h
    puzzlib/src/Core/Inherit.h
    puzzlib/src/Core/Object.h
    puzzlib/src/Containers/Array.h
    puzzlib/src/Containers/TreeMap.h
    puzzlib/src/State/State.h
    puzzlib/src/Event/Event.h
    puzzlib/puzzlib.h
    puzzlib/src/Layer/Layer.h
    puzzlib/src/Event/Listener.h
    puzzlib/src/Event/Dispatcher.h
    puzzlib/src/Puzzles/Logging/component/Log.h
    puzzlib/src/Puzzles/Logging/component/Log.cpp
    puzzlib/src/Puzzles/Logging/layer/LoggingLayer.h
    puzzlib/src/Puzzles/Logging/layer/LoggingLayer.cpp
    puzzlib/src/Puzzles/Keyboard/component/Keyboard.h
    puzzlib/src/Puzzles/Keyboard/component/Keyboard.cpp
    puzzlib/src/Puzzles/Keyboard/layer/KeyboardLayer.h
    puzzlib/src/Puzzles/Keyboard/layer/KeyboardLayer.cpp
    puzzlib/src/Puzzles/Dispatchers/component/Dispatchers.h
    puzzlib/src/Puzzles/Dispatchers/component/Dispatchers.cpp
    puzzlib/src/Puzzles/Dispatchers/layer/DispatchersLayer.h
    puzzlib/src/Puzzles/Dispatchers/layer/DispatchersLayer.cpp
    puzzlib/src/Puzzles/Console/component/Console.h
    puzzlib/src/Puzzles/Console/component/KeyInput.h
    puzzlib/src/Puzzles/Console/component/Sink.h
    puzzlib/src/Puzzles/Console/component/Console.cpp
    puzzlib/src/Puzzles/Console/layer/ConsoleLayer.h
    puzzlib/src/Puzzles/Console/layer/ConsoleLayer.cpp
)

add_library(puzzlib SHARED ${SOURCES} ${HEADERS})

find_path(PDC_INCLUDES curses.h)
find_library(PDC_LIBS pdcurses REQUIRED)

target_link_libraries(puzzlib
    PRIVATE ${PDC_LIBS}
)

target_include_directories(puzzlib PRIVATE
    ${CMAKE_SOURCE_DIR}/puzzlib/src
    ${CMAKE_SOURCE_DIR}/puzzlib/vendor/spdlog/include
    ${PDC_INCLUDES}
)

target_compile_definitions(puzzlib PRIVATE
)