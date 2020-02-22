//
// Created by unkorunk
//

#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Entry.h"

int main() {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cerr << "[GLFW] failed init" << std::endl;
        return 1;
    }

    try {
        Entry::getInstance().awake();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;

        glfwTerminate();
        return 1;
    }

    window = glfwCreateWindow(Settings::getInstance().get<int>("width"),
            Settings::getInstance().get<int>("height"),
            Settings::getInstance().get<std::string>("title").c_str(),
            Settings::getInstance().get<bool>("fullscreen") ? glfwGetPrimaryMonitor() : nullptr,
            nullptr);
    if (!window) {
        std::cerr << "[GLFW] failed create window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "[GLEW] failed init" << std::endl;
        glfwTerminate();
        return 1;
    }

    Entry::getInstance().setWindow(window);

    try {
        Entry::getInstance().start();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;

        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        GLint mask = GL_COLOR_BUFFER_BIT;
        if (Settings::getInstance().get<std::string>("project_type") == "3d") {
            mask |= GL_DEPTH_BUFFER_BIT;
        }
        glClear(mask);

        try {
            Entry::getInstance().update();
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;

            glfwTerminate();
            return 1;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        const char *description;
        if (glfwGetError(&description) != GLFW_NO_ERROR) {
            std::cerr << description << std::endl;

            glfwTerminate();
            return 1;
        }
    }

    glfwTerminate();
    return 0;
}
