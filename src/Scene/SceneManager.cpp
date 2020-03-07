//
// Created by unkorunk on 02.03.2020.
//

#include "SceneManager.h"

SceneManager::SceneManager(Blank* blank) : IManager(blank) {}

IScene *SceneManager::getScene() const {
    return this->selected_scene.get();
}

void SceneManager::update()
{
    this->logic_change_scene();
}

void SceneManager::logic_change_scene()
{
    if (query_scene != nullptr) {
        this->selected_scene = std::unique_ptr<IScene>(query_scene);
        query_scene = nullptr;
        this->selected_scene->start();
    }
}
