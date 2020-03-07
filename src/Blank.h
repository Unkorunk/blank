//
// Created by unkorunk on 03.03.2020.
//

#pragma once

#include <iostream>
#include <exception>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>

#include "ITreeStructure.h"
#include "IManager.h"
#include "Settings.h"
#include "Scene/SceneManager.h"
#include "Mouse/MouseManager.h"
#include "ResourceManager.h"

class Blank {
public:
    Blank();
    virtual ~Blank();

    int run();

    GLFWwindow *getWindow() const;

    template <typename T>
    T* getManager() {
        return managers.getChild<T>();
    }

private:
    GLFWwindow *window;

    ITreeStructure<IManager> managers;

    void awake();
    void start();
    void update();

    std::chrono::system_clock::time_point time_prev_frame;

protected:

};
