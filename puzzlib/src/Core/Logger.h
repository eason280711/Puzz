#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace puzz
{
    class Logger : public Object
    {
    public:
        Logger() {}
        ~Logger() {
        }
        static void startUp() {
            spdlog::set_pattern("%^[%T] [%n] %v%$");
            s_logger = spdlog::stdout_color_mt("PUZZ");
            s_logger->set_level(spdlog::level::trace);
        };
        static void shutDown() {
            s_logger->flush();
            spdlog::drop_all();
        };
        static std::shared_ptr<spdlog::logger>& getLogger() {
            return s_logger;
        };
    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };
    #define CORE_LOG_TRACE(...)    ::puzz::Logger::getLogger()->trace(__VA_ARGS__)
    #define CORE_LOG_DEBUG(...)    ::puzz::Logger::getLogger()->debug(__VA_ARGS__)
    #define CORE_LOG_INFO(...)     ::puzz::Logger::getLogger()->info(__VA_ARGS__)
    #define CORE_LOG_WARN(...)     ::puzz::Logger::getLogger()->warn(__VA_ARGS__)
    #define CORE_LOG_ERROR(...)    ::puzz::Logger::getLogger()->error(__VA_ARGS__)
    #define CORE_LOG_CRITICAL(...) ::puzz::Logger::getLogger()->critical(__VA_ARGS__)
}