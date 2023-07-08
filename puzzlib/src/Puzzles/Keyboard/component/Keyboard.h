#pragma once

#include <chrono>

#include "Core/Core.h"
#include "Core/Inherit.h"

namespace puzz
{
    class KeyboardManager : public Inherit<KeyboardManager, RuntimeModule>
    {
    public:
        ~KeyboardManager() override
        {
        };

        void startUp() override;
        void shutDown() override;
        void Tick() override;

        bool isKeyPressed(int vkey) const;

    private:
        bool m_keyStates[256];
        bool m_keyStatesPrev[256];
        bool m_keyRepeatStarted[256];
        std::chrono::time_point<std::chrono::high_resolution_clock> m_lastKeyPressTime[256];
    };
}