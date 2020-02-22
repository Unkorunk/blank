//
// Created by unkorunk on 20.02.2020.
//

#include "Button.h"

#include <utility>

namespace GUI {
    void Button::draw(Shader *shader) {
        shader->set("use_texture", 0);

        std::array<GLfloat, 6 * 3> vertices = {
                this->getX(), this->getY(), 0.0f,
                this->getX(), this->getY() - this->getHeight(), 0.0f,
                this->getX() + this->getWidth(), this->getY(), 0.0f,

                this->getX() + this->getWidth(), this->getY(), 0.0f,
                this->getX(), this->getY() - this->getHeight(), 0.0f,
                this->getX() + this->getWidth(), this->getY() - this->getHeight(), 0.0f
        };
        std::array<GLfloat, 6 * 4> colors = {};
        for (size_t i = 0; i < 6; i++) {
            colors[4 * i + 0] = 127.0f / 255.0f;
            colors[4 * i + 1] = 127.0f / 255.0f;
            colors[4 * i + 2] = 127.0f / 255.0f;
            colors[4 * i + 3] = 1.0f;
        }

        shader->set(2, colors.size() * sizeof(GLfloat), 4, colors.data());
        shader->set(0, vertices.size() * sizeof(GLfloat), 3, vertices.data());

        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);

        this->execute(&Component::setX, this->getX());
        this->execute(&Component::setY, this->getY());
        this->execute(&Component::draw, shader);
    }

    void Button::mouseDown(float x, float y) {
        this->mouse_event = MouseEvent::MOUSE_DOWN;
        if (this->mouse_down_callback) {
            this->mouse_down_callback(this, x, y);
        }
    }

    void Button::mousePress(float x, float y) {
        this->mouse_event = MouseEvent::MOUSE_PRESS;
        if (this->mouse_press_callback) {
            this->mouse_press_callback(this, x, y);
        }
    }

    void Button::mouseUp(float x, float y) {
        this->mouse_event = MouseEvent::MOUSE_UP;
        if (this->mouse_up_callback) {
            this->mouse_up_callback(this, x, y);
        }
    }

    void Button::mouseMove(float x, float y) {
        this->mouse_event = MouseEvent::MOUSE_MOVE;
        if (this->mouse_move_callback) {
            this->mouse_move_callback(this, x, y);
        }
    }

    void Button::setMouseDownCallback(std::function<void(Button *, float, float)> callback) {
        this->mouse_down_callback = std::move(callback);
    }

    void Button::setMousePressCallback(std::function<void(Button *, float, float)> callback) {
        this->mouse_press_callback = std::move(callback);
    }

    void Button::setMouseUpCallback(std::function<void(Button *, float, float)> callback) {
        this->mouse_up_callback = std::move(callback);
    }

    void Button::setMouseMoveCallback(std::function<void(Button *, float, float)> callback) {
        this->mouse_move_callback = std::move(callback);
    }

    MouseEvent Button::getMouseEvent() const {
        return this->mouse_event;
    }
}
