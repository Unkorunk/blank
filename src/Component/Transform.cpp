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

    void Transform::setZ(float z) {
        this->position.setZ(z);
    }
    float Transform::getZ() const {
        return this->position.getZ();
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

    void Transform::setDepth(float depth) {
        this->size.setZ(depth);
    }
    float Transform::getDepth() const {
        return this->size.getZ();
    }

    void Transform::setPosition(const Vector3f& position) {
        this->position = position;
    }

    void Transform::setPosition(float x, float y, float z) {
        this->position.setX(x);
        this->position.setY(y);
        this->position.setZ(z);
    }

    Vector3f Transform::getPosition() const {
        return this->position;
    }

    void Transform::setSize(const Vector3f& size) {
        this->size = size;
    }

    void Transform::setSize(float width, float height, float depth) {
        this->size.setX(width);
        this->size.setY(height);
        this->size.setZ(depth);
    }

    Vector3f Transform::getSize() const {
        return this->size;
    }

    void Transform::setRotation(const Vector3f& rotation) {
        this->rotation = rotation;
    }
    Vector3f Transform::getRotation() const {
        return this->rotation;
    }
}
