namespace puzz
{
    class Command : public Inherit<abstract_method<Command>, Object>
    {
    public:
        virtual void execute(const std::vector<std::string>& args) = 0;
    };

    class Analyser : public Inherit<Analyser, Object>
    {
    public:
        Analyser()
        {
        }

        static void registerCommand(const std::string& name, const ref_ptr<Command>& command)
        {
            commands[name] = command;
        }

        static void parseAndExecute(const std::string& input)
        {
            std::istringstream iss(input);
            std::string commandName;
            iss >> commandName;

            if (commands.find(commandName) == commands.end())
            {
                PUZZ_CORE_ERROR("Unknown command: {}", commandName);
                return;
            }

            std::vector<std::string> args;
            std::string arg;
            while (iss >> arg)
            {
                args.push_back(arg);
            }

            commands[commandName]->execute(args);
        }

        static TreeMap<std::string, ref_ptr<Command>> getCommands()
        {
            return commands;
        }

    private:
        static TreeMap<std::string, ref_ptr<Command>> commands;
    };

    // TODO: command help
    class HelpCommand : public Inherit<HelpCommand, Command>
    {
    public:
        void execute(const std::vector<std::string>& args) override
        {
            auto commands = Analyser::getCommands();
            PUZZ_CORE_INFO("Available commands:");
            for (auto& [name, command] : commands)
            {
                PUZZ_CORE_INFO("  {}", name);
            }
        }
    };

    // TODO: command exit
    class ExitCommand : public Inherit<ExitCommand, Command>
    {
    public:
        void execute(const std::vector<std::string>& args) override
        {
            PUZZ_CORE_INFO("Exiting...");
            exit(0);
        }
    };

    // TODO: command Dispatch

    class CustomEvent : public Inherit<CustomEvent, Event>
    {
    public:
        CustomEvent(const std::string& name, const std::string& m) : Inherit<CustomEvent, Event>(EventType::CustomEvent,name), msg(m)
        {
        }

        bool Handle() override
        {
            PUZZ_CORE_INFO("[ CustomEvent ] Name: {} , Msg: {}", getName(), msg);
            return true;
        };

    private:
        std::string msg;
    };

    class DispatchCommand : public Inherit<DispatchCommand, Command>
    {
    public:
        void execute(const std::vector<std::string>& args) override
        {
            if (args.size() < 1)
            {
                PUZZ_CORE_ERROR("DispatchCommand: no event message");
                return;
            }
            ref_ptr<Event> customEvent = new CustomEvent(args[0], args[1]);
            auto dispatcher = DispatchersManager::getDispatchers()["System"];
            dispatcher->dispatchEvent(customEvent);
        }
    };

    // TODO: command Reroad Plugin

    class ReloadCommand : public Inherit<ReloadCommand, Command>
    {
    public:
        void execute(const std::vector<std::string>& args) override
        {
            ref_ptr<Event> reloadEvent = new ReloadEvent();
            auto dispatcher = DispatchersManager::getDispatchers()["System"];
            dispatcher->dispatchEvent(reloadEvent);
        }
    };

    // TODO: command LoggingLevel

    class LoggingLevelCommand : public Inherit<LoggingLevelCommand, Command>
    {
    public:
        void execute(const std::vector<std::string>& args) override
        {
            /*
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
            */
            if (args.size() < 1)
            {
                PUZZ_CORE_ERROR("LoggingLevelCommand: no level");
                return;
            }
            if (args[0] == "trace")
            {
                PUZZ_CORE_SET_LEVEL(TRACE);
            }
            else if (args[0] == "debug")
            {
                PUZZ_CORE_SET_LEVEL(DEBUG);
            }
            else if (args[0] == "info")
            {
                PUZZ_CORE_SET_LEVEL(INFO);
            }
            else if (args[0] == "warn")
            {
                PUZZ_CORE_SET_LEVEL(WARN);
            }
            else if (args[0] == "error")
            {
                PUZZ_CORE_SET_LEVEL(ERR);
            }
            else if (args[0] == "critical")
            {
                PUZZ_CORE_SET_LEVEL(CRITICAL);
            }
            else
            {
                PUZZ_CORE_ERROR("LoggingLevelCommand: unknown level");
                // 列出所有level
                PUZZ_CORE_ERROR("LoggingLevelCommand: trace");
                PUZZ_CORE_ERROR("LoggingLevelCommand: debug");
                PUZZ_CORE_ERROR("LoggingLevelCommand: info");
                PUZZ_CORE_ERROR("LoggingLevelCommand: warn");
                PUZZ_CORE_ERROR("LoggingLevelCommand: error");
                PUZZ_CORE_ERROR("LoggingLevelCommand: critical");
            }
        }
    };

    TreeMap<std::string, ref_ptr<Command>> Analyser::commands;
}