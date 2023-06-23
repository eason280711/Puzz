#pragma once
#include "Console.h"

namespace ftxui {

    class ScrollerBase : public ComponentBase {
    public:
        ScrollerBase(Component child, int f) : selected_(f) { Add(child); }

    private:
        Element Render() final {
            auto focused = Focused() ? focus : ftxui::select;
            auto style = Focused() ? bgcolor(Color::GrayLight) : nothing;

            Element background = ComponentBase::Render();
            background->ComputeRequirement();
            size_ = background->requirement().min_y;
            Focused() ? selected_ : selected_ = size_;
            return dbox({
                       std::move(background),
                       vbox({
                           text(L"") | size(HEIGHT, EQUAL, selected_),
                           text(L"") | style | focused,
                       }),
                }) |
                vscroll_indicator | yframe | yflex | reflect(box_);
        }

        bool OnEvent(Event event) final {
            if (event.is_mouse() && box_.Contain(event.mouse().x, event.mouse().y))
                TakeFocus();

            Focused();

            int selected_old = selected_;
            if (event == Event::ArrowUp || event == Event::Character('k') ||
                (event.is_mouse() && event.mouse().button == Mouse::WheelUp)) {
                selected_--;
            }
            if ((event == Event::ArrowDown || event == Event::Character('j') ||
                (event.is_mouse() && event.mouse().button == Mouse::WheelDown))) {
                selected_++;
            }
            if (event == Event::PageDown)
                selected_ += box_.y_max - box_.y_min;
            if (event == Event::PageUp)
                selected_ -= box_.y_max - box_.y_min;
            if (event == Event::Home)
                selected_ = 0;
            if (event == Event::End)
                selected_ = size_;

            selected_ = std::max(0, std::min(size_ - 1, selected_));

            return selected_old != selected_;
        }

        bool Focusable() const final { return true; }

        int selected_ = 0;
        int size_ = 0;
        Box box_;
    };

    Component Scroller(Component child, int f) {
        return Make<ScrollerBase>(std::move(child), f);
    }

    class FocusOnClick : public ComponentBase {
    public:
        FocusOnClick(Component component) : component_(component) {
            Add(component_);
        }

    private:
        Component component_;

        Element Render() final {
            return component_->Render();
        }

        bool OnEvent(Event event) final {
            // If the event is a mouse event and the mouse click event, then take focus.
            if (event.is_mouse() && event.mouse().button == Mouse::Left) {
                component_->TakeFocus();
            }

            // Pass the event to the underlying component.
            return component_->OnEvent(event);
        }

        bool Focusable() const final {
            // This component is focusable only if the underlying component is focusable.
            return component_->Focusable();
        }
    };

    Component MakeFocusOnClick(Component component) {
        return std::make_shared<FocusOnClick>(component);
    }

}  // namespace ftxui