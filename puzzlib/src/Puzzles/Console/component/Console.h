#pragma once

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "Containers/TreeMap.h"
#include <string>

#include <ftxui/component/component.hpp>          // for Container, Input, Renderer
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>                 // for text, vbox, hbox, border
#include <ftxui/component/loop.hpp>

namespace puzz
{
    class ConsoleManager : public Inherit<ConsoleManager, RuntimeModule>
    {
    public:
        ~ConsoleManager(){};

        void startUp() override;
        void shutDown() override;
        void Tick() override;
        void TUIinit();

    private:
        std::string input_content;
        ftxui::Loop *loop;
        ftxui::ScreenInteractive *screen_interactive;
        ftxui::Component *screen, *decorated_input_box, *input_box, *input, *container, *container2, *container3, *output_box;
        std::vector<std::string> logging_content;
    };
}
