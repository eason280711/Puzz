#pragma once

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
        bool m_keyStates[256]; // 監聽所有的鍵盤按鍵
    };
}