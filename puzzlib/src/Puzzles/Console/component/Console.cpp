#include "Console.h"
#include "Event/Dispatcher.h"
#include "Core/ref_ptr.h"
#include "Containers/Array.h"
#include "Containers/TreeMap.h"
#include <string>

#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"

#include <memory>

#include "Sink.h"

#include "Ftxui_ex.h"

#include "TUI.h"

namespace puzz
{

    void ConsoleManager::startUp()
    {
        // analyser = ref_ptr(new Analyser());
        TUIinit();
        std::shared_ptr<spdlog::sinks::sink> new_sink = std::make_shared<mSink>(container2, screen_interactive, 5000);
        LogManager::GetCoreLogger()->sinks().clear();
        LogManager::GetCoreLogger()->sinks().push_back(new_sink);

        PUZZ_CORE_INFO(" ______   __  __     ______     ______");
        PUZZ_CORE_INFO("/\\  == \\ /\\ \\/\\ \\   /\\___  \\   /\\___  \\");
        PUZZ_CORE_INFO("\\ \\  _-/ \\ \\ \\_\\ \\  \\/_/  /__  \\/_/  /__");
        PUZZ_CORE_INFO(" \\ \\_\\    \\ \\_____\\   /\\_____\\   /\\_____\\");
        PUZZ_CORE_INFO("  \\/_/     \\/_____/   \\/_____/   \\/_____/");
    }

    void ConsoleManager::shutDown()
    {
        delete loop;
        delete screen_interactive;
        delete screen;
        delete container;
        delete container2;
        delete container3;
        delete input;
        delete input_box;
        delete decorated_input_box;
        delete output_box;
    }

    void ConsoleManager::Tick()
    {
        loop->RunOnce();
    }
}