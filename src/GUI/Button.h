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
#include "Label.h"
#include "ITreeStructure.h"
#include "IInputMouse.h"

namespace GUI {
    class Button : public Component, public ITreeStructure, public IInputMouse {
    public:
        Button() = default;
        void draw(Shader* shader) override;

    private:

    };
}

#endif //BLANK_GAME_BUTTON_H
