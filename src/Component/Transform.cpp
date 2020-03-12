//
// Created by unkorunk on 05.03.2020.
//

#include "Transform.h"

namespace Component {
    Transform::Transform() : position(), size(1.0f, 1.0f, 1.0f), rotation() {
        this->logic_update_model_matrix();
    }

    void Transform::setX(float x) {
        this->position.setX(x);
        this->logic_update_model_matrix();
    }
    float Transform::getX() const {
        return this->position.getX();
    }

    void Transform::setY(float y) {
        this->position.setY(y);
        this->logic_update_model_matrix();
    }
    float Transform::getY() const {
        return this->position.getY();
    }

    void Transform::setZ(float z) {
        this->position.setZ(z);
        this->logic_update_model_matrix();
    }
    float Transform::getZ() const {
        return this->position.getZ();
    }

    void Transform::setWidth(float width) {
        this->size.setX(width);
        this->logic_update_model_matrix();
    }
    float Transform::getWidth() const {
        return this->size.getX();
    }

    void Transform::setHeight(float height) {
        this->size.setY(height);
        this->logic_update_model_matrix();
    }
    float Transform::getHeight() const {
        return this->size.getY();
    }

    void Transform::setDepth(float depth) {
        this->size.setZ(depth);
        this->logic_update_model_matrix();
    }
    float Transform::getDepth() const {
        return this->size.getZ();
    }

    void Transform::setPosition(const Vector3f& position) {
        this->position = position;
        this->logic_update_model_matrix();
    }
    void Transform::setPosition(float x, float y, float z) {
        this->position.setX(x);
        this->position.setY(y);
        this->position.setZ(z);
        this->logic_update_model_matrix();
    }
    Vector3f Transform::getPosition() const {
        return this->position;
    }

    void Transform::setSize(const Vector3f& size) {
        this->size = size;
        this->logic_update_model_matrix();
    }
    void Transform::setSize(float width, float height, float depth) {
        this->size.setX(width);
        this->size.setY(height);
        this->size.setZ(depth);
        this->logic_update_model_matrix();
    }
    Vector3f Transform::getSize() const {
        return this->size;
    }

    void Transform::setRotation(const Vector3f& rotation) {
        this->rotation = rotation;
        this->logic_update_model_matrix();
    }
    Vector3f Transform::getRotation() const {
        return this->rotation;
    }

    glm::mat4 Transform::getModelMatrix() const {
        return this->model_matrix;
    }

    void Transform::logic_update_model_matrix() {
        this->model_matrix = glm::translate(glm::mat4(1.0f), this->position.toGLM());
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getX(), glm::vec3(1.0f, 0.0f, 0.0f));
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getY(), glm::vec3(0.0f, 1.0f, 0.0f));
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getZ(), glm::vec3(0.0f, 0.0f, 1.0f));
        this->model_matrix = glm::scale(this->model_matrix, this->size.toGLM());
    }
}
