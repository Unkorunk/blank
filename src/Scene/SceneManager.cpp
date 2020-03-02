//
// Created by unkorunk on 02.03.2020.
//

#include "SceneManager.h"

SceneManager &SceneManager::getInstance() {
    static SceneManager sceneManager;
    return sceneManager;
}

IScene *SceneManager::getScene() const {
    return this->selectedScene.get();
}
