#include "LoggingLayer.h"

namespace puzz
{
    ref_ptr<Layer> CreateLoggingLayer()
    {
        ref_ptr<Layer> layer = new LoggingLayer("LoggingLayer");

        ref_ptr<Listener> listener = dynamic_pointer_cast<Layer, Listener>(layer);

        auto keyboardDispatcher = DispatchersManager::getDispatchers()["KeyBoard"];
        keyboardDispatcher->addListener(listener);

        auto systemDispatcher = DispatchersManager::getDispatchers()["System"];
        systemDispatcher->addListener(listener);

        return layer;
    }
}