//
// Created by unkorunk on 13.02.2020.
//

#include "Component.h"

namespace GUI {
    Component::Component() : x(), y(), width(), height() {

    }

    void Component::setX(float x) {
        this->x = x;
    }

    float Component::getX() const {
        return this->x;
    }

    void Component::setY(float y) {
        this->y = y;
    }

    float Component::getY() const {
        return this->y;
    }

    void Component::setWidth(float width) {
        this->width = width;
    }

    float Component::getWidth() const {
        return this->width;
    }

    void Component::setHeight(float height) {
        this->height = height;
    }

    float Component::getHeight() const {
        return this->height;
    }
}