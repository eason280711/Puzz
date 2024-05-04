#include "Core/Visitor.h"
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Render/Renderer.h"
#include <functional>
#include <string>

#include "Event/KeyEvent.h"
#include "Event/WindowEvent.h"


namespace puzz
{
    class CloseEventHandler : public Inherit<Visitor, CloseEventHandler> {
    public:
        using Callback = std::function<void()>;

        CloseEventHandler(Callback callback):m_close(callback) {}
        void apply(WindowClosedEvent& event) override { 
            m_close();
        }
    private:
        Callback m_close;
    };

    class KeyEventHandler : public Inherit<Visitor, KeyEventHandler> {
    public:
        KeyEventHandler(ref_ptr<Renderer> renderer):m_renderer(renderer) {}
        void apply(KeyPressedEvent& event) override { 
            //up 265, down 264, left 263, right 262
            if (event.GetKey() == 265) {
                //m_renderer->updateXY(0, 0, 10);
                m_renderer->getRenderable("red")->update(0, 10);   
            } else if (event.GetKey() == 264){
                //m_renderer->updateXY(0, 0, -10);
                m_renderer->getRenderable("red")->update(0, -10);
            } else if (event.GetKey() == 263) {
                //m_renderer->updateXY(0,-10, 0);
                m_renderer->getRenderable("red")->update(-10, 0);
            } else if (event.GetKey() == 262){
                //m_renderer->updateXY(0,10, 0);
                m_renderer->getRenderable("red")->update(10, 0);
            }
        }
    private:
        ref_ptr<Renderer> m_renderer;
    };
}