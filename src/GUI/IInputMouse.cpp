//
// Created by unkorunk on 22.02.2020.
//

#include "IInputMouse.h"

#include <utility>

namespace GUI {
    IInputMouse::IInputMouse() : mouse_event(MouseEvent::MOUSE_NOT_CONTAINS) {}

    void IInputMouse::mouseEvent(MouseEvent mouse_event, const Vector2f& position) {
        this->mouse_event = mouse_event;
        auto iter = callbacks.find(mouse_event);
        if (iter != callbacks.end() && iter->second) {
            iter->second(position);
        }
    }

    MouseEvent IInputMouse::getMouseEvent() const {
        return this->mouse_event;
    }

    void IInputMouse::setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback) {
        callbacks[mouse_event] = std::move(callback);
    }
}
