#pragma once

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "Containers/TreeMap.h"
#include <windows.h>
#include <curses.h>
#include <string>

namespace puzz {

    class ConsoleManager : public Inherit<ConsoleManager, RuntimeModule>
    {
    public:
        ~ConsoleManager() {};

        void startUp() override;
        void shutDown() override;
        void Tick() override;

    private:
        WINDOW* output_win_box;
        WINDOW* input_win_box;
        WINDOW* output_win;
        WINDOW* input_win;
    };
}
