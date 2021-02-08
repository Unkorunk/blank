//
// Created by unkorunk on 05.03.2020.
//

#pragma once

#include <functional>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "IComponent.h"
#include "Utility/Vector3f.h"

namespace Component {
    class Transform : public IComponent {
    public:
        Transform();

        void start() override;

        void setX(float x);
        float getX() const;

        void setY(float y);
        float getY() const;

        void setZ(float z);
        float getZ() const;

        void setPosition(const Vector3f& position);
        void setPosition(float x, float y, float z);
        Vector3f getPosition() const;

        void setPosition2D(const Vector2f& position);
        void setPosition2D(float x, float y);
        Vector2f getPosition2D() const;

        void setWidth(float width);
        float getWidth() const;

        void setHeight(float height);
        float getHeight() const;

        void setDepth(float depth);
        float getDepth() const;

        void setSize(const Vector3f& size);
        void setSize(float width, float height, float depth);
        Vector3f getSize() const;

        Vector2f getSize2D() const;
        void setSize2D(float width, float height);
        void setSize2D(const Vector2f& size);

        void setRotation(const Vector3f& rotation);
        Vector3f getRotation() const;

        glm::mat4 getModelMatrix() const;

        void setTransformUpdateCallback(std::function<void(Transform*)> callback);

    private:
        Vector3f position, size, rotation;
        glm::mat4 model_matrix;

        Transform* findClosestParentTransform(GameObject* parent) const;
        void updateChildTransform(GameObject* child);

        void updateModelMatrix();

        std::function<void(Transform*)> transform_update_callback;

    };
}
