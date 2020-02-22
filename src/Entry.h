//
// Created by unkorunk on 26.01.2020.
//

#ifndef BLANK_ENTRY_H
#define BLANK_ENTRY_H

#include <string>
#include <map>
#include <chrono>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MouseEvent.h"

#include "Settings.h"

#include "Shader.h"

#include "GUI/Font.h"
#include "GUI/Button.h"
#include "GUI/Label.h"

class Entry {
public:
    static Entry &getInstance();

    void setWindow(GLFWwindow* window);

    void awake();
    void start();
    void update();

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void mouseEnterCallback(GLFWwindow* window, int entered);
    void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

private:
    Entry();
    ~Entry();

    double mouse_position_x, mouse_position_y;
    GLFWwindow* window;

    MouseEvent mouse_event;

    std::unique_ptr<GUI::Font> roboto_font;

    GUI::Button test_button;
    GUI::Label test_label;

    std::chrono::system_clock::time_point time_prev_frame;

    std::map<std::string, Shader> shaders;
};


#endif //BLANK_ENTRY_H
