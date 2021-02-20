#pragma once

#include <functional>
#include <map>

#include "IComponent.h"
#include "Transform.h"
#include "Mouse/MouseManager.h"

namespace Component {
    class InputMouse : public IComponent {
    public:
        InputMouse();
        virtual ~InputMouse() = default;

        void update() override;

        void mouseEvent(MouseEvent mouse_event, const Vector2f& position);
        void setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback);

        Vector2f getMousePosition() const;

        bool check(const MouseEvent& mouse_event) {
            return check(this->mouse_event, mouse_event);
        }

        bool isMove() const {
            return is_move;
        }

        bool isContains() const {
            return is_contains;
        }

        bool isEnter() const {
            return is_enter;
        }

        bool isLeave() const {
            return is_leave;
        }

    private:
        std::map<MouseEvent, std::function<void(const Vector2f&)>> callbacks;
        MouseEvent mouse_event;
        Vector2f mouse_position;

        bool is_move = false, is_contains = false, is_enter = false, is_leave = false;

        void setMouseEvent(const MouseEvent& mouse_event);

        bool check(const MouseEvent& lhs, const MouseEvent& rhs) {
            using T = std::underlying_type_t<MouseEvent>;
            return (static_cast<T>(lhs) & static_cast<T>(rhs)) == static_cast<T>(rhs);
        }

    };
}
