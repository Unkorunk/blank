//
// Created by unkorunk on 22.02.2020.
//

#include "Mouse.h"

Mouse::Mouse()
        : mouse_event(MouseEvent::MOUSE_NOT_CONTAINS), mouse_position_x(), mouse_position_y() {}

Mouse &Mouse::getInstance() {
    static Mouse instance;
    return instance;
}

MouseEvent Mouse::getMouseEvent() const {
    return this->mouse_event;
}

Vector2f Mouse::getMousePosition() const {
    return Vector2f(
            static_cast<float>(this->mouse_position_x),
            static_cast<float>(this->mouse_position_y)
    );
}

void Mouse::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            switch (mouse_event) {
                case MouseEvent::MOUSE_UP:
                case MouseEvent::MOUSE_ENTER:
                case MouseEvent::MOUSE_CONTAINS:
                case MouseEvent::MOUSE_MOVE:
                    mouse_event = MouseEvent::MOUSE_DOWN;
                    break;
                case MouseEvent::MOUSE_DOWN:
                case MouseEvent::MOUSE_PRESS:
                case MouseEvent::MOUSE_LEAVE:
                case MouseEvent::MOUSE_NOT_CONTAINS:
                    throw std::runtime_error("Undefined behavior");
            }
        } else if (action == GLFW_RELEASE) {
            mouse_event = MouseEvent::MOUSE_UP;
        } else {
            throw std::runtime_error("Undefined behavior");
        }
    }
}

void Mouse::mouseEnterCallback(GLFWwindow *window, int entered) {
    if (entered == GLFW_TRUE) {
        this->mouse_event = MouseEvent::MOUSE_ENTER;
    } else if (entered == GLFW_FALSE) {
        this->mouse_event = MouseEvent::MOUSE_LEAVE;
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void Mouse::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    if (this->mouse_event != MouseEvent::MOUSE_PRESS) {
        this->mouse_event = MouseEvent::MOUSE_MOVE;
    }
    this->mouse_position_x = xpos;
    this->mouse_position_y = ypos;
}

void Mouse::update() {
    switch (mouse_event) {
        case MouseEvent::MOUSE_DOWN:
            mouse_event = MouseEvent::MOUSE_PRESS;
            break;
        case MouseEvent::MOUSE_UP:
        case MouseEvent::MOUSE_ENTER:
            mouse_event = MouseEvent::MOUSE_CONTAINS;
            break;
        case MouseEvent::MOUSE_LEAVE:
            mouse_event = MouseEvent::MOUSE_NOT_CONTAINS;
            break;
        default:
            break;
    }
}
