#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"

#include "Event/KeyEvent.h"
#include "Event/WindowEvent.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace puzz
{
    class win32Window : public Inherit<Window, win32Window>
    {
    public:
        win32Window(ref_ptr<WindowTraits> traits)
            : Inherit(traits), m_window(nullptr)
        {
        }

        unsigned int GetWidth() override
        {
            return 0;
        }

        unsigned int GetHeight() override
        {
            return 0;
        }

        void* GetWindow() const override
        {
            return m_window;
        }

        void getFramebufferSize(int& width, int& height) override
        {
            glfwGetFramebufferSize(m_window, &width, &height);
        }

        void startUp() override
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_window = glfwCreateWindow(m_traits->width, m_traits->height, m_traits->title.c_str(), nullptr, nullptr);
            if (m_window == nullptr)
            {
                glfwTerminate();
                throw std::runtime_error("Failed to create GLFW window");
            }

            glfwMakeContextCurrent(m_window);
            glfwSetWindowUserPointer(m_window, m_traits.get());

            // Set GLFW callbacks

            glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                auto traits = static_cast<WindowTraits*>(glfwGetWindowUserPointer(window));
                if (traits->m_callback)
                {
                    switch (action)
                    {
                    case GLFW_PRESS:
                        traits->m_callback(*KeyPressedEvent::create(key, 0));
                        break;
                    case GLFW_RELEASE:
                        traits->m_callback(*KeyReleasedEvent::create(key));
                        break;
                    case GLFW_REPEAT:
                        traits->m_callback(*KeyPressedEvent::create(key, 1));
                        break;
                    }
                }
            });

            glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
                auto traits = static_cast<WindowTraits*>(glfwGetWindowUserPointer(window));
                if (traits->m_callback)
                {
                    traits->m_callback(*WindowClosedEvent::create());
                }
            });
        }

        void Tick(double deltaTime) override
        {
            glfwPollEvents();
        }

        void shutDown() override
        {
            glfwTerminate();
        }

        void swapBuffers() override
        {
            glfwSwapBuffers(m_window);
        }
    private:
        GLFWwindow* m_window;
    };

    ref_ptr<Window> Window::create(ref_ptr<WindowTraits> traits)
    {
        return win32Window::create(traits);
    }
}