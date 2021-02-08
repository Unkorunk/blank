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
        this->query_scene = std::make_unique<T>(std::forward<Args>(args)...);
        this->query_scene->blank = this->getBlank();
        this->query_scene->setShader(this->getBlank()->getManager<ResourceManager>()->getDefaultShader());
        if (!selected_scene) {
            this->changeScene();
        }
    }

    IScene *getScene() const;

    void update(float delta_time) override;

private:
    void changeScene();

    std::unique_ptr<IScene> selected_scene;
    std::unique_ptr<IScene> query_scene;

};
