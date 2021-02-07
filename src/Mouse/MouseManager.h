//
// Created by unkorunk on 22.02.2020.
//

#pragma once

#include <utility>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IManager.h"
#include "MouseEvent.h"
#include "Utility/Vector2f.h"

class MouseManager : public IManager {
public:
    explicit MouseManager(Blank *blank);
    virtual ~MouseManager() = default;

    void start() override;
    void update() override;

    MouseEvent getMouseEvent() const;
    Vector2f getMousePosition() const;

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void mouseEnterCallback(GLFWwindow* window, int entered);
    void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

private:
    MouseEvent mouse_event;
    Vector2f mouse_position;

};
