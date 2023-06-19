// KeyboardManager.h
#pragma once

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include <windows.h>

namespace puzz {

    class KeyboardManager : public Inherit<KeyboardManager, RuntimeModule>
    {
    public:
        ~KeyboardManager() {};

        void startUp() override;
        void shutDown() override;
        void Tick() override;

        bool isKeyPressed(int vkey);

    private:
        bool m_keyStates[256]; // 監聽所有的鍵盤按鍵
    };
}
