#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace puzz
{
    std::shared_ptr<spdlog::logger> LogManager::s_CoreLogger;

    void LogManager::startUp()
    {
        spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %v");

        s_CoreLogger = spdlog::stdout_color_mt("PUZZ");

        s_CoreLogger->set_level(spdlog::level::trace);

        m_LastLogTime = std::chrono::steady_clock::now();
    }

    void LogManager::shutDown()
    {
        s_CoreLogger->flush();
        spdlog::drop_all();
    }

    void LogManager::Tick()
    {
        const auto now = std::chrono::steady_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_LastLogTime);
        if (duration.count() >= 30)
        {
            PUZZ_CORE_TRACE("{0}", "System check for 30 seconds.");
            m_LastLogTime = now;
        }
    }
}