//
// Created by unkorunk on 20.02.2020.
//

#include "Button.h"

namespace GUI {
    void Button::draw(Shader *shader) {
        Component::draw(shader);

        shader->set("use_texture", 0);
        shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());
        shader->set(1, uvs.size() * sizeof(GLfloat), 2, uvs.data());
        shader->set(2, colors.size() * sizeof(GLfloat), 4, colors.data());

        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices_count));

        text.setWidth(std::min(text.getWidth(), this->getWidth() - radius[0] - radius[2]));
        if (text.getHeight() > this->getHeight()) {
            text.setHeight(std::min(text.getHeight(), this->getHeight() - radius[0] - radius[2]));
        }

        float width = this->getWidth() - text.getWidth();
        float height = this->getHeight() - text.getHeight();

        text.setX(this->getX() + width / 2.0f);
        text.setY(this->getY() - height / 2.0f);

        text.draw(shader);
    }

    void Button::setFont(Font* font)
    {
        this->text.setFont(font);
    }

    Font* Button::getFont() const
    {
        return this->text.getFont();
    }

    void Button::setText(const std::string& text)
    {
        this->text.setText(text);
    }

    std::string Button::getText() const
    {
        return this->text.getText();
    }

    void Button::setX(float x)
    {
        Component::setX(x);
        this->refresh();
    }
    void Button::setY(float y)
    {
        Component::setY(y);
        this->refresh();
    }
    void Button::setPosition(const Vector2f& position) {
        Component::setPosition(position);
        this->refresh();
    }

    void Button::setWidth(float width)
    {
        Component::setWidth(width);
        this->refresh();
    }
    void Button::setHeight(float height)
    {
        Component::setHeight(height);
        this->refresh();
    }
    void Button::setSize(const Vector2f& size) {
        Component::setSize(size);
        this->refresh();
    }

    std::vector<glm::vec2> Button::quadraticCurve(glm::vec2 start, glm::vec2 control, glm::vec2 end) {
        std::vector<glm::vec2> points;

        float t = 0.0f;
        while (abs(t - 1.0f) > 1e-4) {
            glm::vec2 point = (1.0f - t) * (1.0f - t) * start + 2.0f * t * (1.0f - t) * control + t * t * end;

            points.push_back(point);

            t += 0.2f;
        }

        glm::vec2 point = (1.0f - t) * (1.0f - t) * start + 2.0f * t * (1.0f - t) * control + t * t * end;
        points.push_back(point);

        return points;
    }

    void Button::refresh()
    {
        radius[0] = this->getWidth() * 0.05f;
        radius[1] = this->getWidth() * 0.05f;
        radius[2] = this->getWidth() * 0.05f;
        radius[3] = this->getWidth() * 0.05f;

        vertices = {
                this->getX() + this->getWidth() / 2.0f, this->getY() - this->getHeight() / 2.0f, 0.0f,

                this->getX() + radius[0], this->getY(), 0.0f,
                this->getX() + this->getWidth() - radius[1], this->getY(), 0.0f
        };

        auto push_vec2 = [this](GLfloat x, GLfloat y) {
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0.0f);
        };

        for (const glm::vec2& point : quadraticCurve(glm::vec2(-radius[1], 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, -radius[1]))) {
            push_vec2(this->getX() + this->getWidth() + point.x, this->getY() + point.y);
        }
        push_vec2(this->getX() + this->getWidth(), this->getY() - radius[1]);
        push_vec2(this->getX() + this->getWidth(), this->getY() - this->getHeight() + radius[2]);
        for (const glm::vec2& point : quadraticCurve(glm::vec2(0.0f, radius[2]),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(-radius[2], 0.0f))) {
            push_vec2(this->getX() + this->getWidth() + point.x, this->getY() - this->getHeight() + point.y);
        }
        push_vec2(this->getX() + this->getWidth() - radius[2], this->getY() - this->getHeight());
        push_vec2(this->getX() + radius[3], this->getY() - this->getHeight());
        for (const glm::vec2& point : quadraticCurve(glm::vec2(radius[3], 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, radius[3]))) {
            push_vec2(this->getX() + point.x, this->getY() - this->getHeight() + point.y);
        }
        push_vec2(this->getX(), this->getY() - this->getHeight() + radius[3]);
        push_vec2(this->getX(), this->getY() - radius[0]);
        for (const glm::vec2& point : quadraticCurve(glm::vec2(0.0f, -radius[0]),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(radius[0], 0.0f))) {
            push_vec2(this->getX() + point.x, this->getY() + point.y);
        }

        vertices_count = vertices.size() / 3;

        colors.resize(vertices_count * 4);
        for (size_t i = 0; i < vertices.size() / 3; i++) {
            colors[4 * i + 0] = 0.0f / 255.0f;
            colors[4 * i + 1] = 149.0f / 255.0f;
            colors[4 * i + 2] = 255.0f / 255.0f;
            colors[4 * i + 3] = 1.0f;
        }
        uvs.resize(vertices_count * 2);
    }
}
