//
// Created by unkorunk on 13.02.2020.
//

#ifndef BLANK_GAME_BUTTON_H
#define BLANK_GAME_BUTTON_H

#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "../Mouse/MouseEvent.h"
#include "Component.h"
#include "Label.h"
#include "IInputMouse.h"

namespace GUI {
    class Button : public Component, public IInputMouse {
    public:
        Button() = default;
        void draw(Shader* shader) override;

        void setFont(Font* font);
        Font* getFont() const;

        void setText(const std::string& text);
        std::string getText() const;

        void setX(float x) override;
        void setY(float y) override;
        void setWidth(float width) override;
        void setHeight(float height) override;

    private:
        float radius[4] = {0.05f, 0.05f, 0.05f, 0.05f};
        std::vector<glm::vec2> quadraticCurve(glm::vec2 start, glm::vec2 control, glm::vec2 end);
        
        size_t vertices_count = 0;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colors;
        std::vector<GLfloat> uvs;

        Label text;

        void refresh();

    };
}

#endif //BLANK_GAME_BUTTON_H
