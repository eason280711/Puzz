#include "Console.h"
#include "Analyzer.h"

namespace puzz
{

    void ConsoleManager::TUIinit()
    {
        Analyser::registerCommand("/help", ref_ptr<Command>(new HelpCommand()));
        Analyser::registerCommand("/exit", ref_ptr<Command>(new ExitCommand()));
        Analyser::registerCommand("/dispatch", ref_ptr<Command>(new DispatchCommand()));
        Analyser::registerCommand("/setlevel", ref_ptr<Command>(new LoggingLevelCommand()));
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
        input_box = new ftxui::Component(ftxui::Input(&input_content, ">", input_option));
        decorated_input_box = new ftxui::Component(Renderer(*input_box, [&]
                                                            { return ftxui::hbox(ftxui::text(" > "), ftxui::text(input_content)) | ftxui::border; }));

        input = new ftxui::Component(MakeFocusOnClick(*decorated_input_box));

        container2 = new ftxui::Component(ftxui::Container::Vertical({}));
        for (int i = 0; i < 1; ++i)
        {
            auto component = ftxui::Renderer([=](bool focused)
                                             {
                auto element = ftxui::text(" ") | ftxui::color(ftxui::Color::Red);
            return element; });
            (*container2)->Add(component);
        }

        container3 = new ftxui::Component(ftxui::Scroller(*container2, 6));

        output_box = new ftxui::Component(Renderer(*container3, [&]
                                                   { return (*container3)->Render(); }) |
                                          ftxui::border);

        // The whole screen.
        container = new ftxui::Component(ftxui::Container::Vertical({
            ftxui::Container::Vertical({*input}),
            ftxui::Container::Vertical({*output_box}),
        }));

        screen = new ftxui::Component(Renderer(*container, [&]
                                               { return ftxui::vbox({(*output_box)->Render() | ftxui::flex,
                                                                     (*decorated_input_box)->Render()}) |
                                                        ftxui::flex; }));

        auto tmp_sc = new ftxui::ScreenInteractive(ftxui::ScreenInteractive::Fullscreen());
        auto tmp_loop = new ftxui::Loop((tmp_sc), *screen);

        tmp_sc->PostEvent(ftxui::Event::Custom);
        screen_interactive = tmp_sc;
        loop = tmp_loop;
    }
}