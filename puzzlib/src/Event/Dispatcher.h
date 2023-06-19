#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Containers/Array.h"
#include "Core/ref_ptr.h"
#include <string>
#include <iostream>

namespace puzz
{
    class Dispatcher : public Inherit<Dispatcher, Object> 
    {
    public:
        void addListener(ref_ptr<Listener> listener) {
            listeners.push_back(listener);
        }

        void removeListener(ref_ptr<Listener> listener) {
            auto it = listeners.find(listener);
            if (it != listeners.end()) {
                listeners.erase(it);
            }
        }

        void dispatchEvent(const Event& event) {
            for (auto it = listeners.begin(); it != listeners.end(); ++it) {
                (*it)->onEvent(event);
            }
        }

        void clear() {
            listeners.clear();
        }
        
    private:
        Array<ref_ptr<Listener>> listeners;  // Using raw pointers for simplicity, consider using smart pointers in real code
    };
}