//
// Created by unkorunk on 22.02.2020.
//

#include "InputMouse.h"
#include "Blank.h"

namespace Component {
    InputMouse::InputMouse() : mouse_event(MouseEvent::MOUSE_NOT_CONTAINS) {}

    void InputMouse::mouseEvent(MouseEvent mouse_event, const Vector2f& position) {
        this->mouse_event = mouse_event;
        auto iter = callbacks.find(mouse_event);
        if (iter != callbacks.end() && iter->second) {
            iter->second(position);
        }
    }

    MouseEvent InputMouse::getMouseEvent() const {
        return this->mouse_event;
    }

    void InputMouse::setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback) {
        callbacks[mouse_event] = std::move(callback);
    }

    void InputMouse::update() {
        int window_width, window_height;
        glfwGetWindowSize(this->getBlank()->getWindow(), &window_width, &window_height);

        Vector2f mouse_position = this->getBlank()->getManager<MouseManager>()->getMousePosition();
        float mouse_x = 2.0f * mouse_position.getX() / window_width - 1.0f,
                mouse_y = -2.0f * mouse_position.getY() / window_height + 1.0f;

        Component::Transform *transform = this->getParent()->getComponent<Component::Transform>();
        if (transform) {
            bool mouse_on_button = (mouse_x > transform->getX() ||
                abs(mouse_x - transform->getX()) < std::numeric_limits<float>::epsilon()) &&
                (mouse_y < transform->getY() ||
                    abs(mouse_y - transform->getY()) < std::numeric_limits<float>::epsilon()) &&
                mouse_x < transform->getX() + transform->getWidth() &&
                mouse_y > transform->getY() - transform->getHeight();

            Vector2f mouse_pos(mouse_x, mouse_y);
            // TODO: improve that logic
            if (mouse_on_button) {
                this->mouseEvent(this->getBlank()->getManager<MouseManager>()->getMouseEvent(), mouse_pos);
            }
            else {
                switch (this->getMouseEvent()) {
                case MouseEvent::MOUSE_MOVE:
                case MouseEvent::MOUSE_PRESS:
                case MouseEvent::MOUSE_DOWN:
                case MouseEvent::MOUSE_CONTAINS:
                case MouseEvent::MOUSE_ENTER:
                case MouseEvent::MOUSE_UP:
                    this->mouseEvent(MouseEvent::MOUSE_LEAVE, mouse_pos);
                    break;

                case MouseEvent::MOUSE_LEAVE:
                    this->mouseEvent(MouseEvent::MOUSE_NOT_CONTAINS, mouse_pos);
                case MouseEvent::MOUSE_NOT_CONTAINS:
                    break;
                default:
                    throw std::runtime_error("Undefined behaviour");
                }
            }
        }
    }
}
