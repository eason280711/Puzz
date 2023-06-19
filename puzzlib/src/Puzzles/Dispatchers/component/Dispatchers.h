#pragma once

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "Containers/TreeMap.h"
#include "Event/Dispatcher.h"
#include <windows.h>
#include <string>

namespace puzz {

    class DispatchersManager : public Inherit<DispatchersManager, RuntimeModule>
    {
    public:
        ~DispatchersManager() {};

        void startUp() override;
        void shutDown() override;
        void Tick() override;

        static TreeMap<std::string,ref_ptr<Dispatcher>> getDispatchers() { return s_Dispatchers; }

    private:
        static TreeMap<std::string, ref_ptr<Dispatcher>> s_Dispatchers;
    };
}
