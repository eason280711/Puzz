#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include <string>
#include <iostream>

namespace puzz
{
    enum class EventType {
        None = 0,
        KeyPressed, KeyReleased, KeyRepeat,
        MouseButtonPressed, MouseButtonReleased, MouseMoved,
        WindowMove, WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMaximize, WindowMinimize,
        ReloadEvent,CustomEvent,
        ExitEvent
    };


    class DataHolder
    {
    public:
        virtual ~DataHolder()
        {
        }
    };

    template <typename T>
    class Data : public DataHolder
    {
    public:
        Data(const T& data) : data(data)
        {
        }

        T get() const { return data; }

    private:
        T data;
    };

    class Event : public Inherit<abstract_method<Event>, Object>
    {
    public:
        Event(EventType type,const std::string& Name) : name(Name), type_(type)
        {
        }

        Event(const std::string& Name) : name(Name), type_(EventType::None)
        {
        }

        ~Event() override
        {
        }

        virtual bool Handle()
        {
            std::cout << getName() << std::endl;
            return true;
        }

        void setName(const std::string& Name) { name = Name; }
        std::string getName() const { return name; }

        void setDataHolder(const ref_ptr<DataHolder>& dataHolder) { dataHolder_ = dataHolder; }

        template <typename T>
        T getData() const
        {
            ref_ptr<Data<T>> data = dynamic_pointer_cast<DataHolder, Data<T>>(dataHolder_);
            return (*data).get();
        }

        EventType getType() const { return type_; }

    private:
        std::string name = "Event";
        ref_ptr<DataHolder> dataHolder_;
        EventType type_;
    };

    class KeyPressEvent : public Inherit<KeyPressEvent, Event>
    {
    public:
        KeyPressEvent() : Inherit<KeyPressEvent, Event>(EventType::KeyPressed, "KeyPressEvent")
        {
        }

        ~KeyPressEvent() override
        {
        }

        bool Handle() override
        {
            return true;
        };

    private:
    };

    class KeyReleaseEvent : public Inherit<KeyReleaseEvent, Event>
    {
    public:
        KeyReleaseEvent() : Inherit<KeyReleaseEvent, Event>(EventType::KeyReleased, "KeyRelease")
        {
        }

        ~KeyReleaseEvent() override
        {
        }

        bool Handle() override
        {
            return true;
        };

    private:
    };

    class KeyRepeatEvent : public Inherit<KeyRepeatEvent, Event>
    {
    public:
        KeyRepeatEvent() : Inherit<KeyRepeatEvent, Event>(EventType::KeyRepeat, "KeyRepeat")
        {
        }

        ~KeyRepeatEvent() override
        {
        }

        bool Handle() override
        {
            return true;
        };

    private:
    };

    class ExitEvent : public Inherit<ExitEvent, Event>
    {
    public:
        ExitEvent() : Inherit<ExitEvent, Event>(EventType::ExitEvent, "ExitEvent")
        {
        }

        ~ExitEvent() override
        {
        }

        bool Handle() override
        {
            return true;
        };

    private:
    };

    class MouseEvents : public Inherit<MouseEvents, Event>
    {
        public:
        MouseEvents() : Inherit<MouseEvents, Event>(EventType::MouseButtonPressed, "MouseEvents")
        {
        }

        ~MouseEvents() override
        {
        }

        bool Handle() override
        {
            return true;
        };
    };

    class WindowMoveEvent: public Inherit<WindowMoveEvent, Event>
    {
        public:
        WindowMoveEvent() : Inherit<WindowMoveEvent, Event>(EventType::WindowMove, "WindowMoveEvent")
        {
        }

        ~WindowMoveEvent()
        {

        }

        bool Handle() override
        {
            return true;
        }
    };

    class ReloadEvent : public Inherit<ReloadEvent, Event>
    {
    public:
        ReloadEvent() : Inherit<ReloadEvent, Event>(EventType::ReloadEvent, "ReloadEvent")
        {
        }

        bool Handle() override
        {
            return true;
        };
    };
}