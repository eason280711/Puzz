#pragma once
#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Event/Dispatcher.h"
#include "Puzzles/Logging/layer/LoggingLayer.h"

#include "Event/Event.h"

namespace puzz
{
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            PUZZ_CORE_DEBUG("Mouse button pressed at time: {}",glfwGetTime());
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int windowWidth, windowHeight;
            glfwGetWindowSize(window, &windowWidth, &windowHeight);

            ref_ptr<Event> event = new MouseEvents();
            auto data = new Data<Array<double>>({ xpos ,ypos,(double)windowWidth,(double)windowHeight});

            event->setDataHolder(dynamic_pointer_cast<Data<Array<double>>, DataHolder>(data));
            Dispatcher::enqeueEvent(event);
        }
    }

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
                800, 800, "Puzz Application", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                throw std::runtime_error("Window has not been created yet");
            }

            SetWindow(window);

            /* Make the window's context current */
            glfwMakeContextCurrent(window);

            glfwSetMouseButtonCallback(window, mouse_button_callback);
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