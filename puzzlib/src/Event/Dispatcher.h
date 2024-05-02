#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include<string>
#include <queue>

namespace puzz
{
    class Dispatcher : public Object
    {
    public:
        // virtual ~Dispatcher() {};
        // static void enqeueEvent(const ref_ptr<KeyEvent>& event)
        // {
        //     eventQueue.push(event);
        // }

        // static std::queue<ref_ptr<KeyEvent>>& getEventQueue()
        // {
        //     return eventQueue;
        // }

        // static void clearEventQueue()
        // {
        //     while (!eventQueue.empty())
        //     {
        //         eventQueue.pop();
        //     }
        // }
    private:
        // static std::queue<ref_ptr<KeyEvent>> eventQueue;
    };
}