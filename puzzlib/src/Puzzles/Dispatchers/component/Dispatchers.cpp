#include "Dispatchers.h"
#include "Event/Dispatcher.h"
#include "Core/ref_ptr.h"
#include "Containers/Array.h"
#include "Containers/TreeMap.h"
#include <string>

namespace puzz {
    TreeMap<std::string, ref_ptr<Dispatcher>> DispatchersManager::s_Dispatchers;

    void DispatchersManager::startUp()
    {
        s_Dispatchers["KeyBoard"] = new Dispatcher();
    }

    void DispatchersManager::shutDown()
    {

    }

    void DispatchersManager::Tick()
    {

    }
}