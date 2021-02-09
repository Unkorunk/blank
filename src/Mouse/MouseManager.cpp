//
// Created by unkorunk on 22.02.2020.
//

#include "MouseManager.h"
#include "Blank.h"

MouseManager::MouseManager(Blank *blank)
        : IManager(blank), mouse_event(MouseEvent::NOT_CONTAINS), mouse_position() {}

MouseEvent MouseManager::getMouseEvent() const {
    return this->mouse_event;
}

Vector2f MouseManager::getMousePosition() const {
    return this->mouse_position;
}

void MouseManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            switch (mouse_event) {
                case MouseEvent::UP:
                case MouseEvent::ENTER:
                case MouseEvent::CONTAINS:
                case MouseEvent::MOVE:
                    mouse_event = MouseEvent::DOWN;
                    break;
                case MouseEvent::DOWN:
                case MouseEvent::PRESS:
                case MouseEvent::LEAVE:
                case MouseEvent::NOT_CONTAINS:
                    throw std::runtime_error("Undefined behavior");
            }
        } else if (action == GLFW_RELEASE) {
            mouse_event = MouseEvent::UP;
        } else {
            throw std::runtime_error("Undefined behavior");
        }
    }
}

void MouseManager::mouseEnterCallback(GLFWwindow *window, int entered) {
    if (entered == GLFW_TRUE) {
        this->mouse_event = MouseEvent::ENTER;
    } else if (entered == GLFW_FALSE) {
        this->mouse_event = MouseEvent::LEAVE;
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void MouseManager::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    this->update(0.0f);
    
    if (this->mouse_event != MouseEvent::PRESS) {
        this->mouse_event = MouseEvent::MOVE;
    }

    this->mouse_position = Vector2f(
        static_cast<float>(xpos),
        static_cast<float>(ypos)
    );
}

void MouseManager::update(float delta_time) {
    switch (mouse_event) {
        case MouseEvent::DOWN:
            mouse_event = MouseEvent::PRESS;
            break;
        case MouseEvent::UP:
        case MouseEvent::ENTER:
            mouse_event = MouseEvent::CONTAINS;
            break;
        case MouseEvent::LEAVE:
            mouse_event = MouseEvent::NOT_CONTAINS;
            break;
        case MouseEvent::MOVE:
            mouse_event = MouseEvent::CONTAINS;
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

void MouseManager::hideCursor() {
    glfwSetInputMode(this->getBlank()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void MouseManager::disableCursor() {
    glfwSetInputMode(this->getBlank()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MouseManager::enableCursor() {
    glfwSetInputMode(this->getBlank()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
