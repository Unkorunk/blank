//
// Created by unkorunk on 13.02.2020.
//

#ifndef BLANK_GAME_BUTTON_H
#define BLANK_GAME_BUTTON_H

#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <GL/glew.h>

#include "../Mouse/MouseEvent.h"
#include "Component.h"
#include "ITreeStructure.h"

namespace GUI {
    class Button : public Component, public ITreeStructure {
    public:
        Button() = default;
        void draw(Shader* shader) override;

        virtual void mouseDown(float x, float y);
        virtual void mousePress(float x, float y);
        virtual void mouseUp(float x, float y);
        virtual void mouseMove(float x, float y);

        void setMouseDownCallback(std::function<void(Button *, float, float)> callback);
        void setMousePressCallback(std::function<void(Button *, float, float)> callback);
        void setMouseUpCallback(std::function<void(Button *, float, float)> callback);
        void setMouseMoveCallback(std::function<void(Button *, float, float)> callback);

        MouseEvent getMouseEvent() const;

    private:
        std::function<void(Button *, float, float)> mouse_down_callback;
        std::function<void(Button *, float, float)> mouse_press_callback;
        std::function<void(Button *, float, float)> mouse_up_callback;
        std::function<void(Button *, float, float)> mouse_move_callback;

        MouseEvent mouse_event;

    };
}

#endif //BLANK_GAME_BUTTON_H
