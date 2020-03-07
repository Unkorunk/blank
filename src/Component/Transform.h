//
// Created by unkorunk on 05.03.2020.
//

#pragma once

#include "IComponent.h"
#include "Utility/Vector2f.h"

namespace Component {
    class Transform : public IComponent {
    public:
        void setX(float x);
        float getX() const;

        void setY(float y);
        float getY() const;

        void setPosition(const Vector2f& position);
        void setPosition(float x, float y);
        Vector2f getPosition() const;

        void setWidth(float width);
        float getWidth() const;

        void setHeight(float height);
        float getHeight() const;

        void setSize(const Vector2f& size);
        void setSize(float width, float height);
        Vector2f getSize() const;

    private:
        Vector2f position, size;
    };
}
