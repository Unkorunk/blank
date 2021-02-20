#include "MouseManager.h"
#include "Blank.h"

MouseManager::MouseManager(Blank *blank) : IManager(blank) {}

Vector2f MouseManager::getMousePosition() const {
    return this->mouse_position;
}

void MouseManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        setMouseEvent(static_cast<MouseKey>(button), MouseEvent::DOWN);
    } else if (action == GLFW_RELEASE) {
        setMouseEvent(static_cast<MouseKey>(button), MouseEvent::UP);
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void MouseManager::mouseEnterCallback(GLFWwindow *window, int entered) {
    if (entered == GLFW_TRUE) {
        this->is_enter = true;
        this->is_contains = true;
    } else if (entered == GLFW_FALSE) {
        this->is_leave = true;
        this->is_contains = false;
    } else {
        throw std::runtime_error("Undefined behavior");
    }
}

void MouseManager::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    this->is_move = true;

    this->mouse_position = Vector2f(
        static_cast<float>(xpos),
        static_cast<float>(ypos)
    );
}

void MouseManager::update(float delta_time) {
    for (auto& it : this->events) {
        this->old_events[it.first] = it.second;
        it.second = MouseEvent::NONE;
    }

    this->is_move = false;
    this->is_enter = false;
    this->is_leave = false;
}

void MouseManager::lateUpdate() {
    for (auto& it : this->events) {
        MouseEvent old_mouse_event = this->getOldMouseEvent(it.first);
        if (!this->check(it.first, MouseEvent::UP) && !this->check(old_mouse_event, MouseEvent::UP)) {
            if (this->check(old_mouse_event, MouseEvent::DOWN) || this->check(old_mouse_event, MouseEvent::PRESS)) {
                setMouseEvent(it.first, MouseEvent::PRESS);
            }
        }
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

void MouseManager::setMouseEvent(const MouseKey& mouse_key, const MouseEvent& mouse_event) {
    using T = std::underlying_type_t<MouseEvent>;
    events[mouse_key] = static_cast<MouseEvent>(static_cast<T>(this->getMouseEvent(mouse_key)) | static_cast<T>(mouse_event));
}

void MouseManager::unsetMouseEvent(const MouseKey& mouse_key, const MouseEvent& mouse_event) {
    using T = std::underlying_type_t<MouseEvent>;
    events[mouse_key] = static_cast<MouseEvent>(static_cast<T>(this->getMouseEvent(mouse_key)) & ~static_cast<T>(mouse_event));
}
