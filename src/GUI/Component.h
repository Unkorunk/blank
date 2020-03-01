//
// Created by unkorunk on 13.02.2020.
//

#ifndef BLANK_GAME_COMPONENT_H
#define BLANK_GAME_COMPONENT_H

#include <string>
#include <array>

#include <GL/glew.h>

#include "../Settings.h"
#include "../Shader.h"
#include "../Utility/Vector2f.h"

namespace GUI {
    class Component {
    public:
        Component();
        virtual ~Component() = default;

        virtual void draw(Shader* shader);

        virtual void setX(float x);
        virtual float getX() const;

        virtual void setY(float y);
        virtual float getY() const;

        virtual void setPosition(const Vector2f& position);
        virtual Vector2f getPosition() const;

        virtual void setWidth(float width);
        virtual float getWidth() const;

        virtual void setHeight(float height);
        virtual float getHeight() const;

        virtual void setSize(const Vector2f& size);
        virtual Vector2f getSize() const;

    protected:
        Vector2f position, size;
    };
}

#endif //BLANK_GAME_COMPONENT_H
