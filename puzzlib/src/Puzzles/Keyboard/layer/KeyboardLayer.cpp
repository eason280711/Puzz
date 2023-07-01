#include "KeyboardLayer.h"

namespace puzz
{
    ref_ptr<Layer> CreateKeyboardLayer()
    {
        ref_ptr<Layer> layer = new KeyboardLayer("KeyboardLayer");

        return layer;
    }
}