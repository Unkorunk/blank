#include "InputMouse.h"
#include "Blank.h"

namespace Component {
    InputMouse::InputMouse() : mouse_event(MouseEvent::NONE) {}

    void InputMouse::mouseEvent(MouseEvent mouse_event, const Vector2f& position) {
        for (const auto& it : callbacks) {
            using T = std::underlying_type_t<MouseEvent>;
            if (static_cast<T>(it.first) & static_cast<T>(mouse_event)) {
                it.second(position);
            }
        }
    }

    void InputMouse::setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback) {
        callbacks[mouse_event] = std::move(callback);
    }

    void InputMouse::update() {
        MouseEvent old_mouse_event = this->mouse_event;
        bool old_is_contains = this->is_contains;

        this->mouse_event = MouseEvent::NONE;
        this->is_contains = false;
        this->is_enter = false;
        this->is_leave = false;
        this->is_move = false;

        Vector2f mouse_position = this->getBlank()->unProj(
            this->getBlank()->getManager<MouseManager>()->getMousePosition()
        );

        Component::Transform* transform = this->getParent()->getComponent<Component::Transform>();
        MouseManager* mouse = this->getBlank()->getManager<MouseManager>();

        if (!transform || !mouse) {
            throw std::exception();
        }

        glm::vec4 mouse_in_obj_coordinates = glm::inverse(transform->getModelMatrix()) *
            glm::vec4(mouse_position.getX(), mouse_position.getY(), -1.0f, 1.0f);

        this->mouse_position = Vector2f(mouse_in_obj_coordinates.x, mouse_in_obj_coordinates.y);

        if (mouse_in_obj_coordinates.x >= 0 && mouse_in_obj_coordinates.x <= 1 &&
            mouse_in_obj_coordinates.y <= 0 && mouse_in_obj_coordinates.y >= -1) {
            if (!old_is_contains) {
                this->is_enter = true;
            }

            this->is_contains = true;

            bool press_or_down = this->check(old_mouse_event, MouseEvent::DOWN) ||
                this->check(old_mouse_event, MouseEvent::PRESS);

            if (mouse->check(MouseKey::BUTTON_LEFT, MouseEvent::DOWN)) {
                this->setMouseEvent(MouseEvent::DOWN);
            } else if (press_or_down && mouse->check(MouseKey::BUTTON_LEFT, MouseEvent::PRESS)) {
                this->setMouseEvent(MouseEvent::PRESS);
            }

            if (press_or_down && mouse->check(MouseKey::BUTTON_LEFT, MouseEvent::UP)) {
                this->setMouseEvent(MouseEvent::UP);
            }

            if (mouse->isMove()) {
                this->is_move = true;
            }
        } else {
            if (old_is_contains) {
                this->is_leave = true;
            }
        }
    }

    void InputMouse::setMouseEvent(const MouseEvent& mouse_event) {
        using T = std::underlying_type_t<MouseEvent>;
        this->mouse_event = static_cast<MouseEvent>(static_cast<T>(this->mouse_event) | static_cast<T>(mouse_event));
        this->mouseEvent(mouse_event, this->mouse_position);
    }

    Vector2f InputMouse::getMousePosition() const {
        return this->mouse_position;
    }
}
