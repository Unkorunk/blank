//
// Created by unkorunk on 02.03.2020.
//

#ifndef BLANK_GAME_SCENEMANAGER_H
#define BLANK_GAME_SCENEMANAGER_H

#include <memory>

#include "IScene.h"

class SceneManager {
public:
    static SceneManager& getInstance();

    template <typename T, typename... Args>
    void createScene(Args&&... args) {
        selectedScene = std::unique_ptr<IScene>(new T(std::forward<Args>(args)...));
    }

    IScene *getScene() const;

private:
    SceneManager() = default;

    std::unique_ptr<IScene> selectedScene;
};


#endif //BLANK_GAME_SCENEMANAGER_H
