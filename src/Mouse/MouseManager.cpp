//
// Created by unkorunk on 22.02.2020.
//

#include "MouseManager.h"
#include "Blank.h"

MouseManager::MouseManager(Blank *blank)
        : IManager(blank), mouse_event(MouseEvent::MOUSE_NOT_CONTAINS), mouse_position_x(), mouse_position_y() {

}

MouseEvent MouseManager::getMouseEvent() const {
    return this->mouse_event;
}

Vector2f MouseManager::getMousePosition() const {
    return Vector2f(
            static_cast<float>(this->mouse_position_x),
            static_cast<float>(this->mouse_position_y)
    );
}

void MouseManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
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

void MouseManager::mouseEnterCallback(GLFWwindow *window, int entered) {
    if (entered == GLFW_TRUE) {
        this->mouse_event = MouseEvent::MOUSE_ENTER;
    } else if (entered == GLFW_FALSE) {
        this->mouse_event = MouseEvent::MOUSE_LEAVE;
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void MouseManager::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    this->update();
    if (this->mouse_event != MouseEvent::MOUSE_PRESS) {
        this->mouse_event = MouseEvent::MOUSE_MOVE;
    }
    this->mouse_position_x = xpos;
    this->mouse_position_y = ypos;
}

void MouseManager::update() {
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
        case MouseEvent::MOUSE_MOVE:
            mouse_event = MouseEvent::MOUSE_CONTAINS;
            break;
        default:
            break;
    }
}

void MouseManager::start() {
    glfwSetMouseButtonCallback(this->getBlank()->getWindow(), [](GLFWwindow* window, int button, int action, int mods) {
        Blank* blank = static_cast<Blank*>(glfwGetWindowUserPointer(window));
        blank->getManager<MouseManager>()->mouseButtonCallback(window, button, action, mods);
    });
    glfwSetCursorEnterCallback(this->getBlank()->getWindow(), [](GLFWwindow* window, int entered) {
        Blank* blank = static_cast<Blank*>(glfwGetWindowUserPointer(window));
        blank->getManager<MouseManager>()->mouseEnterCallback(window, entered);
    });
    glfwSetCursorPosCallback(this->getBlank()->getWindow(), [](GLFWwindow* window, double xpos, double ypos) {
        Blank* blank = static_cast<Blank*>(glfwGetWindowUserPointer(window));
        blank->getManager<MouseManager>()->mouseMoveCallback(window, xpos, ypos);
    });
}
