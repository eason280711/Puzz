#pragma once
#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Event/Dispatcher.h"
#include "Puzzles/Logging/layer/LoggingLayer.h"

namespace puzz
{
    class WindowManager : public Inherit<WindowManager, RuntimeModule>
    {
    public:
        WindowManager(std::function<GLFWwindow* ()> getWindow,std::function<void(GLFWwindow*)> setWindow) {
            windowCallback = getWindow;
            SetWindow = setWindow;
        }
        ~WindowManager() override {}

        void startUp() override
        {
            if (!glfwInit()) return;

            GLFWwindow* window = glfwCreateWindow(
                800, 600, "Magnum Plain GLFW Triangle Example", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                throw std::runtime_error("Window has not been created yet");
            }

            SetWindow(window);

            /* Make the window's context current */
            glfwMakeContextCurrent(window);
        }

        void shutDown() override
        {
            auto window = windowCallback();
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void Tick() override
        {
        }
    private:
        std::function < GLFWwindow* ()> windowCallback;
        std::function < void(GLFWwindow*)> SetWindow;
    };
}