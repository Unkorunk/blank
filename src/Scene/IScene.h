//
// Created by unkorunk on 02.03.2020.
//

#pragma once

#include "Component/IComponent.h"

#include "ITreeStructure.h"
#include "ResourceManager.h"
#include "GameObject/GameObject.h"

class IScene : public ITreeStructure<GameObject> {
    friend class SceneManager;
public:
    virtual void start() = 0;
    virtual void update(float delta_time) = 0;

    Shader *getShader() const {
        return selected_shader;
    }

private:
    Shader *selected_shader = nullptr;
    Blank* blank = nullptr;

    void logic_update_blank(GameObject* target) {
        target->blank = this->blank;
        for (Component::IComponent* component : target->components.getChildren()) {
            component->blank = this->blank;
        }
        for (GameObject* child : target->getChildren()) {
            logic_update_blank(child);
        }
    }

protected:
    IScene() = default;

    Blank* getBlank() const {
        return blank;
    }

    void setShader(Shader *shader) {
        this->selected_shader = shader;
    }

    bool addChildCallback(GameObject *child) override {
        logic_update_blank(child);
        return true;
    }

};
