//
// Created by unkorunk on 05.03.2020.
//

#include "Transform.h"
#include "../GameObject/GameObject.h"

namespace Component {
    Transform::Transform() : position(), size(1.0f, 1.0f, 1.0f), rotation() {}

    void Transform::start() {
        this->updateModelMatrix();
    }

    void Transform::setX(float x) {
        this->position.setX(x);
        this->updateModelMatrix();
    }
    float Transform::getX() const {
        return this->position.getX();
    }

    void Transform::setY(float y) {
        this->position.setY(y);
        this->updateModelMatrix();
    }
    float Transform::getY() const {
        return this->position.getY();
    }

    void Transform::setZ(float z) {
        this->position.setZ(z);
        this->updateModelMatrix();
    }
    float Transform::getZ() const {
        return this->position.getZ();
    }

    void Transform::setWidth(float width) {
        this->size.setX(width);
        this->updateModelMatrix();
    }
    float Transform::getWidth() const {
        return this->size.getX();
    }

    void Transform::setHeight(float height) {
        this->size.setY(height);
        this->updateModelMatrix();
    }
    float Transform::getHeight() const {
        return this->size.getY();
    }

    void Transform::setDepth(float depth) {
        this->size.setZ(depth);
        this->updateModelMatrix();
    }
    float Transform::getDepth() const {
        return this->size.getZ();
    }

    void Transform::setPosition(const Vector3f& position) {
        this->position = position;
        this->updateModelMatrix();
    }
    void Transform::setPosition(float x, float y, float z) {
        this->position.setX(x);
        this->position.setY(y);
        this->position.setZ(z);
        this->updateModelMatrix();
    }
    Vector3f Transform::getPosition() const {
        return this->position;
    }

    void Transform::setPosition2D(const Vector2f& position) {
        this->position.setX(position.getX());
        this->position.setY(position.getY());
        this->updateModelMatrix();
    }
    void Transform::setPosition2D(float x, float y) {
        this->position.setX(x);
        this->position.setY(y);
        this->updateModelMatrix();
    }
    Vector2f Transform::getPosition2D() const {
        return Vector2f(this->position.getX(), this->position.getY());
    }

    void Transform::setSize(const Vector3f& size) {
        this->size = size;
        this->updateModelMatrix();
    }
    void Transform::setSize(float width, float height, float depth) {
        this->size.setX(width);
        this->size.setY(height);
        this->size.setZ(depth);
        this->updateModelMatrix();
    }
    Vector3f Transform::getSize() const {
        return this->size;
    }

    void Transform::setSize2D(const Vector2f& size) {
        this->size.setX(size.getX());
        this->size.setY(size.getY());
        this->updateModelMatrix();
    }
    void Transform::setSize2D(float width, float height) {
        this->size.setX(width);
        this->size.setY(height);
        this->updateModelMatrix();
    }
    Vector2f Transform::getSize2D() const {
        return Vector2f(this->size.getX(), this->size.getY());
    }

    void Transform::setRotation(const Vector3f& rotation) {
        this->rotation = rotation;
        this->updateModelMatrix();
    }
    Vector3f Transform::getRotation() const {
        return this->rotation;
    }

    glm::mat4 Transform::getModelMatrix() const {
        return this->model_matrix;
    }

    Transform* Transform::findClosestParentTransform(GameObject* parent) const {
        if (parent == nullptr) {
            return nullptr;
        }

        Transform* transform = parent->getComponent<Transform>();
        if (transform) {
            return transform;
        }

        return findClosestParentTransform(parent->getParent());
    }

    void Transform::updateChildTransform(GameObject* child) {
        if (Transform* child_transform = child->getComponent<Transform>()) {
            child_transform->updateModelMatrix();
            return;
        }

        for (GameObject* child : child->getChildren()) {
            updateChildTransform(child);
        }
    }

    void Transform::updateModelMatrix() {
        glm::mat4 parent_model_matrix(1.0f);
        if (Transform* parent_transform = findClosestParentTransform(this->getParent()->getParent())) {
            parent_model_matrix = parent_transform->getModelMatrix();
        }

        this->model_matrix = glm::translate(parent_model_matrix, this->position.toGLM());
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getX(), glm::vec3(1.0f, 0.0f, 0.0f));
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getY(), glm::vec3(0.0f, 1.0f, 0.0f));
        this->model_matrix = glm::rotate(this->model_matrix, this->rotation.getZ(), glm::vec3(0.0f, 0.0f, 1.0f));
        this->model_matrix = glm::scale(this->model_matrix, this->size.toGLM());

        for (GameObject* child : this->getParent()->getChildren()) {
            updateChildTransform(child);
        }

        if (this->transform_update_callback) {
            this->transform_update_callback(this);
        }
    }

    void Transform::setTransformUpdateCallback(std::function<void(Transform*)> callback) {
        this->transform_update_callback = std::move(callback);
    }
}
