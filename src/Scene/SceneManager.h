//
// Created by unkorunk on 02.03.2020.
//

#pragma once

#include <memory>

#include "IScene.h"
#include "IManager.h"

class SceneManager : public IManager {
public:
    explicit SceneManager(Blank* blank);
    virtual ~SceneManager() = default;

    template <typename T, typename... Args>
    void create(Args... args) {
        if (query_scene != nullptr) {
            delete query_scene;
        }
        this->query_scene = new T(std::forward<Args>(args)...);
        this->query_scene->blank = this->getBlank();
        this->query_scene->setShader(this->getBlank()->getManager<ResourceManager>()->getDefaultShader());
        if (!selected_scene) {
            this->logic_change_scene();
        }
    }

    IScene *getScene() const;

    void update() override;

private:
    void logic_change_scene();

    std::unique_ptr<IScene> selected_scene;
    IScene* query_scene = nullptr;

};
