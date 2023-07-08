#pragma once
#include "Keyboard.h"
#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"
#include "Event/Event.h"
#include <windows.h>
#include <string>

namespace puzz
{
    void KeyboardManager::startUp()
    {
        memset(m_keyStates, 0, sizeof m_keyStates);
        memset(m_keyStatesPrev, 0, sizeof m_keyStatesPrev);
        memset(m_lastKeyPressTime, 0, sizeof m_lastKeyPressTime);
        memset(m_keyRepeatStarted, 0, sizeof m_keyRepeatStarted);
    }

    void KeyboardManager::shutDown()
    {
    }

    void KeyboardManager::Tick()
    {
        memcpy(m_keyStatesPrev, m_keyStates, sizeof m_keyStates);

        for (int i = 0; i < 256; ++i)
        {
            m_keyStates[i] = GetAsyncKeyState(i) & 0x8000;
        }

        auto currentTime = std::chrono::high_resolution_clock::now();

        int repeatDelay, repeatRate;
        SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &repeatDelay, 0);
        SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &repeatRate, 0);

        double repeatDelayInSeconds = (repeatDelay + 1) * 0.25;
        double repeatRateInSeconds = 1.0 / (repeatRate + 2);

        for (int i = 0; i < 256; ++i)
        {
            if (m_keyStates[i])
            {
                ref_ptr<Event> event;
                auto data = new Data(i);

                if (!m_keyStatesPrev[i])
                {
                    event = new KeyPressEvent();
                    m_lastKeyPressTime[i] = currentTime;
                    m_keyRepeatStarted[i] = false;
                }
                else
                {
                    std::chrono::duration<double> elapsed = currentTime - m_lastKeyPressTime[i];

                    if (!m_keyRepeatStarted[i] && elapsed.count() > repeatDelayInSeconds)
                    {
                        event = new KeyRepeatEvent();
                        m_lastKeyPressTime[i] = currentTime;
                        m_keyRepeatStarted[i] = true;
                    }
                    else if (m_keyRepeatStarted[i] && elapsed.count() > repeatRateInSeconds)
                    {
                        event = new KeyRepeatEvent();
                        m_lastKeyPressTime[i] = currentTime;
                    }
                }

                if (event)
                {
                    event->setDataHolder(dynamic_pointer_cast<Data<int>, DataHolder>(data));

                    const auto dispatcher = DispatchersManager::getDispatchers()["KeyBoard"];
                    dispatcher->dispatchEvent(event);
                }
            }
            else if (m_keyStatesPrev[i])
            {
                auto event = new KeyReleaseEvent();
                auto data = new Data(i);
                event->setDataHolder(dynamic_pointer_cast<Data<int>, DataHolder>(data));

                const auto dispatcher = DispatchersManager::getDispatchers()["KeyBoard"];
                dispatcher->dispatchEvent(event);
                m_keyRepeatStarted[i] = false;
            }
        }
    }



    bool KeyboardManager::isKeyPressed(const int vkey) const
    {
        return m_keyStates[vkey];
    }
}