//
// Created by unkorunk on 03.03.2020.
//

#pragma once

#include <utility>
#include <string>

#include "ITreeStructure.h"
#include "Component/IComponent.h"

class Blank;

class GameObject : public ITreeStructure<GameObject> {
    friend class IScene;
public:
    GameObject();
    explicit GameObject(std::string name);

    virtual void update();

    void addComponent(Component::IComponent* component);

    template <typename T>
    T* getComponent() const {
        return components.getChild<T>();
    }

    void removeComponent(Component::IComponent* component);

private:
    std::string name;
    ITreeStructure<Component::IComponent> components;

    Blank* blank = nullptr;

protected:
    Blank* getBlank() const {
        return blank;
    }

};
