#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"

namespace puzz
{
    class WindowManager : public Inherit<WindowManager, RuntimeModule>
    {
    public:
        WindowManager(std::function<GLFWwindow* ()> getWindowCallback,std::function<void(GLFWwindow*)> SetWindow) {
            windowCallback = getWindowCallback;
            setWindow = SetWindow;
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

            setWindow(window);

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
        std::function < void(GLFWwindow*)> setWindow;
    };
}