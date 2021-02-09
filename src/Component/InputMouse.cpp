//
// Created by unkorunk on 22.02.2020.
//

#include "InputMouse.h"
#include "Blank.h"

namespace Component {
    InputMouse::InputMouse() : mouse_event(MouseEvent::NOT_CONTAINS) {}

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
        static bool init = false;
        if (!init) {
            this->prev_mouse_position = this->getBlank()->getManager<MouseManager>()->getMousePosition();
            init = true;
        }

        Vector2f mouse_position = this->getBlank()->unProj(
            this->getBlank()->getManager<MouseManager>()->getMousePosition()
        );

        Component::Transform *transform = this->getParent()->getComponent<Component::Transform>();
        if (transform) {
            glm::vec4 mouse_in_obj_coordinates = glm::inverse(transform->getModelMatrix()) *
                glm::vec4(mouse_position.getX(), mouse_position.getY(), -1.0f, 1.0f);

            bool mouse_on_button = (mouse_in_obj_coordinates.x >= 0 && mouse_in_obj_coordinates.x <= 1 &&
                mouse_in_obj_coordinates.y <= 0 && mouse_in_obj_coordinates.y >= -1);

            int next_state[9][9] = {
                    {1, 1, 2, 8, 8, 5, 8, 1},
                    {8, 1, 2, 8, 8, 5, 8, 8},
                    {0, 8, 8, 8, 4, 5, 8, 7},
                    {0, 7, 8, 8, 4, 5, 8, 7},
                    {0, 7, 4, 8, 4, 5, 8, 7},
                    {8, 8, 8, 3, 8, 8, 6, 8},
                    {8, 8, 8, 3, 8, 8, 6, 8},
                    {0, 8, 4, 8, 4, 5, 8, 7},
                    {8, 8, 8, 8, 8, 8, 8, 8}
            };

            if (mouse_on_button) {
                MouseEvent new_state = this->getBlank()->getManager<MouseManager>()->getMouseEvent();
                if ((this->getMouseEvent() == MouseEvent::MOVE || this->getMouseEvent() == MouseEvent::CONTAINS) &&
                    new_state == MouseEvent::PRESS) {
                    if (Vector2f::distanceSqr(prev_mouse_position, mouse_position) > 1e-4) {
                        new_state = MouseEvent::MOVE;
                    }
                    else {
                        new_state = MouseEvent::CONTAINS;
                    }
                }

                if (this->getMouseEvent() == MouseEvent::NOT_CONTAINS || this->getMouseEvent() == MouseEvent::LEAVE) {
                    this->mouseEvent(MouseEvent::ENTER, mouse_position);
                }
                else {
                    if (this->getMouseEvent() == MouseEvent::PRESS && new_state == MouseEvent::MOVE) {
                        this->mouseEvent(MouseEvent::UP, mouse_position);
                        this->mouseEvent(MouseEvent::MOVE, mouse_position);
                    } else {
                        auto ns = static_cast<MouseEvent>(next_state[static_cast<int>(this->getMouseEvent())][static_cast<int>(new_state)]);
                        this->mouseEvent(ns, mouse_position);
                    }
                }

                if (this->getMouseEvent() == MouseEvent::UNDEFINED_BEHAVIOUR) {
                    throw std::runtime_error("Undefined behaviour");
                }
            }
            else {
                switch (this->getMouseEvent()) {
                case MouseEvent::MOVE:
                case MouseEvent::PRESS:
                case MouseEvent::DOWN:
                case MouseEvent::CONTAINS:
                case MouseEvent::ENTER:
                case MouseEvent::UP:
                    this->mouseEvent(MouseEvent::LEAVE, mouse_position);
                    break;

                case MouseEvent::LEAVE:
                    this->mouseEvent(MouseEvent::NOT_CONTAINS, mouse_position);
                case MouseEvent::NOT_CONTAINS:
                    break;
                default:
                    throw std::runtime_error("Undefined behaviour");
                }
            }
        }

        this->prev_mouse_position = mouse_position;
    }
}
