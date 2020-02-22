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

#include "Mouse/MouseEvent.h"

#include "Settings.h"

#include "Shader.h"

#include "GUI/Font.h"
#include "GUI/Button.h"
#include "GUI/Label.h"
#include "Mouse/Mouse.h"

class Entry {
public:
    static Entry &getInstance();

    void setWindow(GLFWwindow* window);

    void awake();
    void start();
    void update();

private:
    Entry();
    ~Entry();

    GLFWwindow* window;

    std::unique_ptr<GUI::Font> roboto_font;

    GUI::Button test_button;
    GUI::Label test_label;

    std::chrono::system_clock::time_point time_prev_frame;

    std::map<std::string, Shader> shaders;
};

#endif //BLANK_ENTRY_H
