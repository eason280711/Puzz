#include "ConsoleLayer.h"
#include "Puzzles/Dispatchers/component/Dispatchers.h"

namespace puzz
{
    ref_ptr<Layer> CreateConsoleLayer()
    {
        ref_ptr<Layer> layer = new ConsoleLayer("ConsoleLayer");

        return layer;
    }
}