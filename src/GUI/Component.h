//
// Created by unkorunk on 13.02.2020.
//

#ifndef BLANK_GAME_COMPONENT_H
#define BLANK_GAME_COMPONENT_H

#include <GL/glew.h>

#include "../Shader.h"

namespace GUI {
    class Component {
    public:
        Component();
        virtual ~Component() = default;

        virtual void draw(Shader* shader) = 0;

        virtual void setX(float x);
        virtual float getX() const;

        virtual void setY(float y);
        virtual float getY() const;

        virtual void setWidth(float width);
        virtual float getWidth() const;

        virtual void setHeight(float height);
        virtual float getHeight() const;

    protected:
        float x, y, width, height;
    };
}

#endif //BLANK_GAME_COMPONENT_H
