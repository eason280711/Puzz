#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Containers/Array.h"
#include "Core/ref_ptr.h"

namespace puzz
{
    class Dispatcher : public Inherit<Dispatcher, Object>
    {
    public:
        void addListener(const ref_ptr<Listener>& listener)
        {
            listeners.push_back(listener);
        }

        void removeListener(const ref_ptr<Listener>& listener)
        {
            const auto it = listeners.find(listener);
            if (it != listeners.end())
            {
                listeners.erase(it);
            }
        }

        void dispatchEvent(const ref_ptr<Event>& event)
        {
            for (auto it = listeners.begin(); it != listeners.end(); ++it)
            {
                (*it)->onEvent(event);
            }
        }

        void clear()
        {
            listeners.clear();
        }

    private:
        Array<ref_ptr<Listener>> listeners;
    };
}