#include "LoggingLayer.h"

namespace puzz
{
    ref_ptr<Layer> CreateLoggingLayer()
    {
        ref_ptr<Layer> layer = new LoggingLayer("LoggingLayer");

        const ref_ptr<Listener> listener = dynamic_pointer_cast<Layer, Listener>(layer);

        const auto keyboardDispatcher = DispatchersManager::getDispatchers()["KeyBoard"];
        keyboardDispatcher->addListener(listener);

        const auto systemDispatcher = DispatchersManager::getDispatchers()["System"];
        systemDispatcher->addListener(listener);

        return layer;
    }
}