#pragma once

#include "Event/Event.h"
#include "Core/Inherit.h"

namespace puzz
{
    class KeyPressedEvent : public Inherit<Event, KeyPressedEvent> {
    public:
        KeyPressedEvent(int key,bool isRepeat):m_key(key),m_isRepeat(isRepeat) {}
        std::string ToString() override { 
            if(m_isRepeat)
                return "KeyRepeatEvent: " + std::to_string(m_key);
            else
                return "KeyPressedEvent: " + std::to_string(m_key);
        }
        int GetKey() { return m_key; }
    private:
        int m_key;
        bool m_isRepeat;
    };

    class KeyReleasedEvent : public Inherit<Event, KeyReleasedEvent> {
    public:
        KeyReleasedEvent(int key):m_key(key) {}
        std::string ToString() override { 
            return "KeyReleasedEvent: " + std::to_string(m_key);
        }
    private:
        int m_key;
    };
}