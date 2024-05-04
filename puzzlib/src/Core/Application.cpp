#include "Core/Core.h"
#include "Application.h"
#include "Containers/Array.h"
#include "Core/Object.h"
#include "Core/Visitor.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Core/Inherit.h"
#include "Event/Dispatcher.h"
#include "Core/Logger.h"

#include <queue>
#include <string>
#include <iostream>
#include <queue>
#include <functional>

#include "Core/Window.h"
#include "Core/UI.h"
#include "Render/Renderer.h"
#include "Core/WindowEventHandler.h"

#include "Core/Timestamp.h"

#include "Render/Renderable.h"
#include "Render/Texture.h"

#include "glm/glm.hpp"

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    void Application::Run()
    {
    }

    void Application::Init()
    {

    }

    void Application::ShotDown()
    {
    }

    void Application::onEvent(Event& e)
    {
    }
}