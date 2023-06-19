// KeyboardManager.cpp
#include "Keyboard.h"
#include "Puzzles/Logging/component/Log.h"
#include <windows.h>

namespace puzz {

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
                    PUZZ_CORE_INFO("Key {} is pressed.", i);
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
