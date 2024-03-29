#include "Core/Core.h"
#include "Core/Inherit.h"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <chrono>

namespace puzz
{
    class PUZZ_API LogManager : public Inherit<LogManager, RuntimeModule>
    {
    public:
        ~LogManager() override
        {
        };

        void startUp() override;
        void shutDown() override;
        void Tick() override;

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        std::chrono::steady_clock::time_point m_LastLogTime;
    };

    // Core Log macro
#define PUZZ_CORE_TRACE(...) ::puzz::LogManager::GetCoreLogger()->trace(__VA_ARGS__);
#define PUZZ_CORE_INFO(...) ::puzz::LogManager::GetCoreLogger()->info(__VA_ARGS__);
#define PUZZ_CORE_WARN(...) ::puzz::LogManager::GetCoreLogger()->warn(__VA_ARGS__);
#define PUZZ_CORE_ERROR(...) ::puzz::LogManager::GetCoreLogger()->error(__VA_ARGS__);
#define PUZZ_CORE_FATAL(...) ::puzz::LogManager::GetCoreLogger()->critical(__VA_ARGS__);
#define PUZZ_CORE_DEBUG(...) ::puzz::LogManager::GetCoreLogger()->debug(__VA_ARGS__);

#define PUZZ_CORE_SET_LEVEL(level) ::puzz::LogManager::GetCoreLogger()->set_level(level);

#define OFF spdlog::level::off
#define CRITICAL spdlog::level::critical
#define ERR spdlog::level::err
#define WARN spdlog::level::warn
#define INFO spdlog::level::info
#define DEBUG spdlog::level::debug
#define TRACE spdlog::level::trace
}