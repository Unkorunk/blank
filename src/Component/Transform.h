//
// Created by unkorunk on 05.03.2020.
//

#pragma once

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

        void setWidth(float width);
        float getWidth() const;

        void setHeight(float height);
        float getHeight() const;

        void setDepth(float depth);
        float getDepth() const;

        void setSize(const Vector3f& size);
        void setSize(float width, float height, float depth);
        Vector3f getSize() const;

        void setRotation(const Vector3f& rotation);
        Vector3f getRotation() const;

        glm::mat4 getModelMatrix() const;

    private:
        Vector3f position, size, rotation;
        glm::mat4 model_matrix;

        Transform* findClosestParentTransform(GameObject* parent) const;
        void updateChildTransform(GameObject* child);

        void logic_update_model_matrix();

    };
}
