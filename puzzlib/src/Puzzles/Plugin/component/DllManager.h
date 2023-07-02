#pragma once

#include "Core/Core.h"
#include "Core/Inherit.h"
#include <windows.h>
#include <string>

namespace puzz
{
    class DllManager : public Inherit<DllManager, RuntimeModule>
    {
    public:
        DllManager(std::string name, std::string path)
            : m_path(path), m_hinstLib(nullptr)
        {
        }

        ~DllManager() override
        {
        };

        void startUp() override
        {
            m_hinstLib = LoadLibrary(TEXT(m_path.c_str()));

            auto SetLogger = getFunction<void(*)(std::shared_ptr<spdlog::logger>)>("SetLogger");

            if (SetLogger != nullptr)
            {
                SetLogger(::puzz::LogManager::GetCoreLogger());
            }
        }

        void shutDown() override
        {
            FreeLibrary(m_hinstLib);
        }

        void Tick() override
        {
        }

        template <typename T>
        T getFunction(const std::string& name)
        {
            return (T)GetProcAddress(m_hinstLib, name.c_str());
        }

    private:
        std::string m_path;
        HINSTANCE m_hinstLib;
    };
}