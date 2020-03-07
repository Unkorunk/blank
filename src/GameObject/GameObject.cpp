//
// Created by unkorunk on 03.03.2020.
//

#include "GameObject.h"

GameObject::GameObject() : name("default") {}

GameObject::GameObject(std::string name) : name(std::move(name)) {}

void GameObject::update() {
    for (Component::IComponent *component : components.getChildren()) {
        component->update();
    }

    for (GameObject *game_object : this->getChildren()) {
        game_object->update();
    }
}

void GameObject::addComponent(Component::IComponent *component) {
    component->parent = this;
    component->blank = this->blank;
    // TODO: call that before first update
    component->start();
    components.addChild(component);
}

void GameObject::removeComponent(Component::IComponent *component) {
    components.removeChild(component);
}
