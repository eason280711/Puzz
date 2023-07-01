#pragma once
#include <spdlog/sinks/base_sink.h>
#include <mutex>

#include <ftxui/component/component.hpp>          // for Container, Input, Renderer
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>                 // for text, vbox, hbox, border

#include <ftxui/component/event.hpp>

namespace puzz
{
    std::mutex time_mutex;

    class mSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        mSink(ftxui::Component* container, ftxui::ScreenInteractive* sci, const int m) : container_(container),
            ScI(sci), cnt(0), maxcnt(m)
        {
        }

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            const auto time_t_time = std::chrono::system_clock::to_time_t(msg.time);

            tm* tm_time;
            {
                std::lock_guard lock(time_mutex);
                tm_time = std::localtime(&time_t_time);
            }

            char time_str[64];
            strftime(time_str, sizeof time_str, "%Y-%m-%d %H:%M:%S", tm_time);

            const std::string level_str = to_string_view(msg.level).data();
            const std::string logger_name_str = to_string(msg.logger_name);
            const std::string payload_str = to_string(msg.payload);

            const auto component = ftxui::Renderer([=](bool focused)
            {
                auto color = ftxui::color(ftxui::Color::GreenLight);

                if (level_str == "trace") color = ftxui::color(ftxui::Color::GrayDark);
                if (level_str == "debug") color = ftxui::color(ftxui::Color::BlueLight);
                if (level_str == "info") color = ftxui::color(ftxui::Color::GreenLight);
                if (level_str == "warn") color = ftxui::color(ftxui::Color::YellowLight);
                if (level_str == "error") color = ftxui::color(ftxui::Color::RedLight);
                if (level_str == "critical") color = ftxui::color(ftxui::Color::Red);
                if (level_str == "off") color = ftxui::color(ftxui::Color::GrayDark);

                auto element = ftxui::text(
                        "  " + std::format("[{}] [{}] [{}]: {}", time_str, level_str, logger_name_str, payload_str)) |
                    color;
                return element;
            });
            (*container_)->Add(component);
            if (cnt > maxcnt)
                (*container_)->ChildAt(0)->Detach();
            ScI->PostEvent(ftxui::Event::Custom);

            //
            cnt += 1;
        }

        void flush_() override
        {
        }

    private:
        ftxui::Component* container_;
        ftxui::ScreenInteractive* ScI;
        int cnt, maxcnt;
    };
}