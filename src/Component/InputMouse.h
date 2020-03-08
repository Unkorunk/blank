//
// Created by unkorunk on 22.02.2020.
//

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

        void start() override;
        void update() override;

        void mouseEvent(MouseEvent mouse_event, const Vector2f& position);
        void setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback);
        MouseEvent getMouseEvent() const;

    private:
        std::map<MouseEvent, std::function<void(const Vector2f&)>> callbacks;
        MouseEvent mouse_event;
        Vector2f prev_mouse_position;

    };
}
