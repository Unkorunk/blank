//
// Created by unkorunk on 22.02.2020.
//

#include "IInputMouse.h"

#include <utility>

namespace GUI {
    void IInputMouse::mouseEvent(MouseEvent mouse_event, float x, float y) {
        this->mouse_event = mouse_event;
        auto iter = callbacks.find(mouse_event);
        if (iter != callbacks.end() && iter->second) {
            iter->second(x, y);
        }
    }

    MouseEvent IInputMouse::getMouseEvent() const {
        return this->mouse_event;
    }

    void IInputMouse::setMouseCallback(MouseEvent mouse_event, std::function<void(float, float)> callback) {
        callbacks[mouse_event] = std::move(callback);
    }
}
