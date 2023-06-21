#include "Console.h"
#include "Event/Dispatcher.h"
#include "Core/ref_ptr.h"
#include "Containers/Array.h"
#include "Containers/TreeMap.h"
#include <string>

#include <curses.h>
#include <Windows.h>
#include <memory>

#include "Sink.h"
#include "Puzzles/Logging/component/Log.h"

namespace puzz {

    void ConsoleManager::startUp()
    {
        initscr();
        cbreak();
        noecho();

        curs_set(0);

        output_win_box = newwin(LINES - 3, COLS, 0, 0);
        input_win_box = newwin(3, COLS, LINES - 3, 0);

        output_win = derwin(output_win_box, LINES - 5, COLS - 2, 1, 2);
        input_win = derwin(input_win_box, 1, COLS - 2, 1, 2);
        scrollok(output_win, TRUE);

        wborder(output_win_box, ' ', ' ', ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        box(input_win_box, 0, 0);

        wprintw(input_win, ">");

        wrefresh(input_win);

        wrefresh(input_win_box);
        wrefresh(output_win_box);

        std::shared_ptr<spdlog::sinks::sink> new_sink = std::make_shared<CursesSink>(output_win, output_win_box);
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
        delwin(output_win);
        delwin(input_win);
        delwin(output_win_box);
        delwin(input_win_box);
        endwin();
    }

    void ConsoleManager::Tick()
    {

    }
}