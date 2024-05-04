#pragma once
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "Core/Inherit.h"

#include <chrono>

namespace puzz
{
    class Timestamp : public Inherit<Object, Timestamp>
    {
    public:
        Timestamp()
        : m_startTime(std::chrono::steady_clock::now())
        , m_previousTime(m_startTime)
        {
        }

        void update()
        {
            m_previousTime = std::chrono::steady_clock::now();
        }

        double getElapsedSeconds() const
        {
            return std::chrono::duration<double>(std::chrono::steady_clock::now() - m_previousTime).count();
        }

        double getTotalSeconds() const
        {
            return std::chrono::duration<double>(std::chrono::steady_clock::now() - m_startTime).count();
        }
    private:
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_previousTime;
    };
}