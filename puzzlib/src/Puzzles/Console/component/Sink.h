#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <mutex>
#include <curses.h>
#include <mutex>

namespace puzz
{
    std::mutex time_mutex;

    class CursesSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        CursesSink(WINDOW* window, WINDOW* border) : win_(window), win_border(border) {
        }

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override {
            auto time_t_time = std::chrono::system_clock::to_time_t(msg.time);

            struct tm* tm_time;
            {
                std::lock_guard<std::mutex> lock(time_mutex);
                tm_time = std::localtime(&time_t_time);
            }

            char time_str[64];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_time);

            std::string level_str = spdlog::level::to_string_view(msg.level).data();
            std::string logger_name_str = fmt::to_string(msg.logger_name);
            std::string payload_str = fmt::to_string(msg.payload);

            wprintw(win_, "\n[%s] [%s] [%s]: %s", time_str, level_str.c_str(), logger_name_str.c_str(), payload_str.c_str());

            wrefresh(win_);
            wrefresh(win_border);
        }


        void flush_() override {
            wrefresh(win_);
        }

    private:
        WINDOW* win_;
        WINDOW* win_border;
    };

}