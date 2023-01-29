#include "Application.h"
#include "Containers/Array.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "State/State.h"
#include "Event/Event.h"
#include <iostream>
#include <string>

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    class MeunState : public Inherit<MeunState, State>
    {
    public:
        MeunState(std::string name) : Inherit<MeunState, State>(name) {};
    };

    class LoginState : public Inherit<LoginState, State>
    {
    public:
        LoginState(std::string name) : Inherit<LoginState, State>(name) {};
    };

    class SettingState : public Inherit<SettingState, State>
    {
    public:
        SettingState(std::string name) : Inherit<SettingState, State>(name) {};
    };

    class QAState : public Inherit<QAState, State>
    {
    public:
        QAState(std::string name) : Inherit<QAState, State>(name) {};
    };

    class LoginEvent : public Inherit<LoginEvent, Event>
    {
    public:
        LoginEvent(std::string name) : Inherit<LoginEvent, Event>(name) {};
    };

    class SettingEvent : public Inherit<SettingEvent, Event>
    {
    public:
        SettingEvent(std::string name) : Inherit<SettingEvent, Event>(name) {};
    };

    class QAEvent : public Inherit<QAEvent, Event>
    {
    public:
        QAEvent(std::string name) : Inherit<QAEvent, Event>(name) {};
    };

    class BackEvent : public Inherit<BackEvent, Event>
    {
    public:
        BackEvent(std::string name) : Inherit<BackEvent, Event>(name) {};
    };

    void Application::Run()
    {
        std::cout << "Hello Application" << std::endl;
        
        // 狀態機測試
        ref_ptr<StateManager> stateManager = ref_ptr<StateManager>(new StateManager());

        // 初始化State
        ref_ptr<State> meunState = ref_ptr<State>(new MeunState("MeunState"));
        ref_ptr<State> loginState = ref_ptr<State>(new LoginState("LoginState"));
        ref_ptr<State> settingState = ref_ptr<State>(new SettingState("SettingState"));
        ref_ptr<State> qaState = ref_ptr<State>(new QAState("QAState"));

        // 初始化Event
        ref_ptr<Event> loginEvent = ref_ptr<Event>(new LoginEvent("LoginEvent"));
        ref_ptr<Event> settingEvent = ref_ptr<Event>(new SettingEvent("SettingEvent"));
        ref_ptr<Event> qaEvent = ref_ptr<Event>(new QAEvent("QAEvent"));
        ref_ptr<Event> backEvent = ref_ptr<Event>(new BackEvent("BackEvent"));

        // 設定State的Transition List
        meunState -> setTransList({{loginEvent, loginState}, {settingEvent, settingState}, {qaEvent, qaState}});
        loginState -> setTransList({{backEvent, meunState}});
        settingState -> setTransList({{backEvent, meunState}});
        qaState -> setTransList({{backEvent, meunState}});

        // 設定初始狀態
        stateManager -> Update(meunState);

        while (true)
        {
            stateManager -> Tick();
        }
    };

    void Application::Init()
    {
    }

    void Application::ShotDown()
    {
    }
}