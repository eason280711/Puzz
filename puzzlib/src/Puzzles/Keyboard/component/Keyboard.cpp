// KeyboardManager.cpp
#pragma once
#include "Keyboard.h"
#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"
#include <windows.h>
#include <string>

namespace puzz {

    class KeyPressEvent : public Inherit<KeyPressEvent, Event>
    {
    public:
        KeyPressEvent(std::string name, int key) : Inherit<KeyPressEvent, Event>(name), code(key) {}
        ~KeyPressEvent() {}

        virtual bool Handle() override
        {
            std::string log = "[" + getName() + "]" + " Key: " + std::to_string(code) + " is pressed";
            PUZZ_CORE_TRACE(log);
            return true;
        };
    private:
        int code;

    };

    void KeyboardManager::startUp()
    {
        memset(m_keyStates, 0, sizeof(m_keyStates));
    }

    void KeyboardManager::shutDown()
    {

    }

    void KeyboardManager::Tick()
    {
        for (int i = 0; i < 256; ++i)
        {
            if (GetAsyncKeyState(i) & 0x8000)
            {
                if (!m_keyStates[i])
                {
                    ref_ptr<Event> keypressEvent = new KeyPressEvent("KeyPressEvent",i);

                    auto dispatcher = DispatchersManager::getDispatchers()["KeyBoard"];

                    dispatcher->dispatchEvent(keypressEvent);

                    m_keyStates[i] = true;
                }
            }
            else
            {
                m_keyStates[i] = false;
            }
        }
    }

    bool KeyboardManager::isKeyPressed(int vkey)
    {
        return m_keyStates[vkey];
    }
}
