//
// Created by unkorunk on 13.02.2020.
//

#pragma once

#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "UIComponent.h"
#include "Label.h"
#include "Mouse/MouseEvent.h"
#include "Component/InputMouse.h"

namespace GUI {
    class Button : public UIComponent {
    public:
        Button();
        void draw(Shader* shader) override;

        void setFont(Font* font);
        Font* getFont() const;

        void setText(const std::string& text);
        std::string getText() const;

        void setX(float x);
        void setY(float y);
        void setPosition(const Vector2f& position);
        void setWidth(float width);
        void setHeight(float height);
        void setSize(const Vector2f& size);

        MouseEvent getMouseEvent() const;
        void setMouseCallback(MouseEvent mouse_event, std::function<void(const Vector2f&)> callback);

    private:
        float radius[4] = {0.05f, 0.05f, 0.05f, 0.05f};
        std::vector<glm::vec2> quadraticCurve(glm::vec2 start, glm::vec2 control, glm::vec2 end);

        std::unique_ptr<Component::InputMouse> input_mouse;

        size_t vertices_count = 0;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colors;
        std::vector<GLfloat> uvs;

        Label text;

        void refresh();

    };
}
