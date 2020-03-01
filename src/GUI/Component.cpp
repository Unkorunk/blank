//
// Created by unkorunk on 13.02.2020.
//

#include "Component.h"

namespace GUI {
    Component::Component() : position(), size() {}

    void Component::setX(float x) {
        this->position.setX(x);
    }

    float Component::getX() const {
        return this->position.getX();
    }

    void Component::setY(float y) {
        this->position.setY(y);
    }

    float Component::getY() const {
        return this->position.getY();
    }

    void Component::setWidth(float width) {
        this->size.setX(width);
    }

    float Component::getWidth() const {
        return this->size.getX();
    }

    void Component::setHeight(float height) {
        this->size.setY(height);
    }

    float Component::getHeight() const {
        return this->size.getY();
    }

    void Component::draw(Shader *shader) {
        if (Settings::getInstance().get<bool>("debug")) {
            shader->set("use_texture", 0);

            std::array<GLfloat, 8 * 3> vertices = {
                    this->getX(), this->getY(), 0.0f,
                    this->getX() + this->getWidth(), this->getY(), 0.0f,
                    this->getX() + this->getWidth(), this->getY(), 0.0f,
                    this->getX() + this->getWidth(), this->getY() - this->getHeight(), 0.0f,
                    this->getX() + this->getWidth(), this->getY() - this->getHeight(), 0.0f,
                    this->getX(), this->getY() - this->getHeight(), 0.0f,
                    this->getX(), this->getY() - this->getHeight(), 0.0f,
                    this->getX(), this->getY(), 0.0f
            };
            std::array<GLfloat, 8 * 4> colors = {};
            for (size_t i = 0; i < 8; i++) {
                colors[4 * i + 0] = 1.0f;
                colors[4 * i + 1] = 0.0f;
                colors[4 * i + 2] = 0.0f;
                colors[4 * i + 3] = 1.0f;
            }

            shader->set(2, colors.size() * sizeof(GLfloat), 4, colors.data());
            shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());

            glDrawArrays(GL_LINES, 0, 2 * 4);
        }
    }

    void Component::setPosition(const Vector2f& position) {
        this->position = position;
    }

    Vector2f Component::getPosition() const {
        return this->position;
    }

    void Component::setSize(const Vector2f& size) {
        this->size = size;
    }

    Vector2f Component::getSize() const {
        return this->size;
    }
}