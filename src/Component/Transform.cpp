//
// Created by unkorunk on 05.03.2020.
//

#include "Transform.h"

namespace Component {
    void Transform::setX(float x) {
        this->position.setX(x);
    }

    float Transform::getX() const {
        return this->position.getX();
    }

    void Transform::setY(float y) {
        this->position.setY(y);
    }

    float Transform::getY() const {
        return this->position.getY();
    }

    void Transform::setWidth(float width) {
        this->size.setX(width);
    }

    float Transform::getWidth() const {
        return this->size.getX();
    }

    void Transform::setHeight(float height) {
        this->size.setY(height);
    }

    float Transform::getHeight() const {
        return this->size.getY();
    }

    void Transform::setPosition(const Vector2f& position) {
        this->position = position;
    }

    void Transform::setPosition(float x, float y) {
        this->position.setX(x);
        this->position.setY(y);
    }

    Vector2f Transform::getPosition() const {
        return this->position;
    }

    void Transform::setSize(const Vector2f& size) {
        this->size = size;
    }

    void Transform::setSize(float width, float height) {
        this->size.setX(width);
        this->size.setY(height);
    }

    Vector2f Transform::getSize() const {
        return this->size;
    }
}