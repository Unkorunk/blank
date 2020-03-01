//
// Created by unkorunk on 22.02.2020.
//

#ifndef BLANK_GAME_MOUSE_H
#define BLANK_GAME_MOUSE_H

#include <utility>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "MouseEvent.h"
#include "../Utility/Vector2f.h"

class Mouse {
    friend class Entry;
public:
    static Mouse &getInstance();

    MouseEvent getMouseEvent() const;
    Vector2f getMousePosition() const;

private:
    Mouse();
    virtual ~Mouse() = default;

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void mouseEnterCallback(GLFWwindow* window, int entered);
    void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

    void update();

    MouseEvent mouse_event;
    double mouse_position_x, mouse_position_y;

};


#endif //BLANK_GAME_MOUSE_H
