//
// Created by unkorunk on 22.02.2020.
//

#ifndef BLANK_GAME_IINPUTMOUSE_H
#define BLANK_GAME_IINPUTMOUSE_H

#include <functional>
#include <map>

#include "../Mouse/MouseEvent.h"

namespace GUI {
    class IInputMouse {
    public:
        void mouseEvent(MouseEvent mouse_event, float x, float y);

        void setMouseCallback(MouseEvent mouse_event, std::function<void(float, float)> callback);

        MouseEvent getMouseEvent() const;

    private:
        std::map<MouseEvent, std::function<void(float, float)>> callbacks;

        MouseEvent mouse_event;

    };
}

#endif //BLANK_GAME_IINPUTMOUSE_H
