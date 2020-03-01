//
// Created by unkorunk on 22.02.2020.
//

#ifndef BLANK_GAME_IINPUTMOUSE_H
#define BLANK_GAME_IINPUTMOUSE_H

#include <functional>
#include <map>

#include "../Mouse/MouseEvent.h"
#include "../Utility/Vector2f.h"

namespace GUI {
    class IInputMouse {
    public:
        virtual ~IInputMouse() = default;

        void mouseEvent(MouseEvent mouse_event, const Vector2f& position);
        void setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback);
        MouseEvent getMouseEvent() const;

    private:
        std::map<MouseEvent, std::function<void(const Vector2f&)>> callbacks;
        MouseEvent mouse_event;

    protected:
        IInputMouse();

    };
}

#endif //BLANK_GAME_IINPUTMOUSE_H
