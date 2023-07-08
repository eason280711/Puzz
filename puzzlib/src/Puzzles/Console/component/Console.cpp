#include "Console.h"
#include "Core/ref_ptr.h"
#include "Containers/Array.h"
#include <string>

#include "Puzzles/Logging/component/Log.h"

#include <memory>

#include "Sink.h"

#include "Ftxui_ex.h"

#include "Analyzer.h"

namespace puzz
{
    void ConsoleManager::startUp()
    {
        // analyser = ref_ptr(new Analyser());
        TUIinit();
        const std::shared_ptr<spdlog::sinks::sink> new_sink = std::make_shared<mSink>(
            container2, screen_interactive, 100);
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

    void ConsoleManager::TUIinit()
    {
        Analyser::registerCommand("/help", ref_ptr<Command>(new HelpCommand()));
        Analyser::registerCommand("/exit", ref_ptr<Command>(new ExitCommand()));
        Analyser::registerCommand("/dispatch", ref_ptr<Command>(new DispatchCommand()));
        Analyser::registerCommand("/setlevel", ref_ptr<Command>(new LoggingLevelCommand()));
        Analyser::registerCommand("/reload", ref_ptr<Command>(new ReloadCommand()));

        // The input box.
        auto input_option = ftxui::InputOption();
        std::string input_add_content = "";
        input_option.on_enter = [&]
        {
            if (input_content.size() > 1)
            {
                PUZZ_CORE_INFO("INPUT CODE : {}", input_content);
                Analyser::parseAndExecute(input_content);
            }
            input_content = "";
        };
        input_box = new ftxui::Component(Input(&input_content, ">", input_option));
        decorated_input_box = new ftxui::Component(Renderer(*input_box, [&]
            {
                return hbox(
                    ftxui::text(" > "), ftxui::text(input_content)) |
                    ftxui::border;
            }));

        input = new ftxui::Component(MakeFocusOnClick(*decorated_input_box));

        container2 = new ftxui::Component(ftxui::Container::Vertical({}));
        for (int i = 0; i < 1; ++i)
        {
            const auto component = ftxui::Renderer([=](bool focused)
                {
                    auto element = ftxui::text(" ") | color(ftxui::Color::Red);
                    return element;
                });
            (*container2)->Add(component);
        }

        container3 = new ftxui::Component(ftxui::Scroller(*container2, 6));

        output_box = new ftxui::Component(Renderer(*container3, [&]
            {
                return (*container3)->Render();
            }) |
            ftxui::border);

        // The whole screen.
        container = new ftxui::Component(ftxui::Container::Vertical({
            ftxui::Container::Vertical({*input}),
            ftxui::Container::Vertical({*output_box}),
            }));

        screen = new ftxui::Component(Renderer(*container, [&]
            {
                return ftxui::vbox({
                        (*output_box)->Render() | ftxui::flex,
                        (*decorated_input_box)->Render()
                    }) |
                    ftxui::flex;
            }));

        const auto tmp_sc = new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen());
        const auto tmp_loop = new ftxui::Loop(tmp_sc, *screen);

        tmp_sc->PostEvent(ftxui::Event::Custom);
        screen_interactive = tmp_sc;
        loop = tmp_loop;
    }
}