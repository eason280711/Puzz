#pragma once
#include "Keyboard.h"
#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"
#include "Event/Event.h"
#include <windows.h>
#include <string>

namespace puzz
{
    class KeyPressEvent : public Inherit<KeyPressEvent, Event>
    {
    public:
        KeyPressEvent(std::string name) : Inherit<KeyPressEvent, Event>(name)
        {
        }

        ~KeyPressEvent() override
        {
        }

        bool Handle() override
        {
            return true;
        };

    private:
    };

    void KeyboardManager::startUp()
    {
        memset(m_keyStates, 0, sizeof m_keyStates);
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
                    const ref_ptr<Event> keypressEvent = new KeyPressEvent("KeyPressEvent");
                    ref_ptr data = new Data(i);
                    keypressEvent->setDataHolder(dynamic_pointer_cast<Data<int>, DataHolder>(data));

                    const auto dispatcher = DispatchersManager::getDispatchers()["KeyBoard"];

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

    bool KeyboardManager::isKeyPressed(const int vkey) const
    {
        return m_keyStates[vkey];
    }
}