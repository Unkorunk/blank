//
// Created by unkorunk on 26.01.2020.
//

#include "Entry.h"

Entry::Entry() : window() {}

Entry::~Entry() = default;

Entry &Entry::getInstance() {
    static Entry entry;
    return entry;
}

void Entry::awake() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Entry::start() {
    for (auto &shader_name : Settings::getInstance().getShaders()) {
        shaders.try_emplace(shader_name, shader_name);
    }

    glClearColor(0.0f, 0.3f, 0.65f, 0.0f);
    if (Settings::getInstance().get<std::string>("project_type") == "3d") {
        glEnable(GL_DEPTH_TEST);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {
        Mouse::getInstance().mouseButtonCallback(window, button, action, mods);
    });
    glfwSetCursorEnterCallback(this->window, [](GLFWwindow *window, int entered) {
        Mouse::getInstance().mouseEnterCallback(window, entered);
    });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos) {
        Mouse::getInstance().mouseMoveCallback(window, xpos, ypos);
    });

    IScene* scene = SceneManager::getInstance().getScene();
    if (scene != nullptr) {
        scene->start();
    }

    time_prev_frame = std::chrono::system_clock::now();
}

void Entry::update() {
    std::chrono::system_clock::time_point time_now_frame = std::chrono::system_clock::now();
    auto delta_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            time_now_frame - time_prev_frame).count();
    time_prev_frame = time_now_frame;
    float delta_time = delta_time_ms / 1000.0f;

    IScene* scene = SceneManager::getInstance().getScene();
    if (scene != nullptr) {
        scene->update();
    }

    Mouse::getInstance().update();
}

void Entry::setWindow(GLFWwindow* window) {
    this->window = window;
}
