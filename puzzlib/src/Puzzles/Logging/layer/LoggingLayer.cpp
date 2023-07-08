#include "LoggingLayer.h"

namespace puzz
{
    ref_ptr<Layer> CreateLoggingLayer()
    {
        ref_ptr<Layer> layer = new LoggingLayer("LoggingLayer");

        const ref_ptr<Listener> listener = dynamic_pointer_cast<Layer, Listener>(layer);

        RegisterDispatcher("KeyBoard",listener);
        RegisterDispatcher("System",listener);

        return layer;
    }
}