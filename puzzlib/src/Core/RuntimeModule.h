#pragma once
#include "Core/Object.h"

namespace puzz
{

    class RuntimeModule : public Object
    {
    public:
        virtual ~RuntimeModule(){};

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick(double deltaTime) = 0;

        void setUpdateInterval(double interval) { m_updateInterval = interval; }
        double getUpdateInterval() const { return m_updateInterval; }
    private:
        double m_updateInterval = 1.0 / 60.0;
    };

}