//
// Created by unkorunk on 26.01.2020.
//

#include "Entry.h"

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
    std::ifstream settings_ifs("settings.json");
    if (!settings_ifs.is_open()) {
        throw std::logic_error("[settings.json] not found file");
    }

    json settings_json;
    settings_ifs >> settings_json;
    settings_ifs.close();

    if (!settings_json.contains("shaders")) {
        throw std::logic_error("[settings.json] not contains key - shaders");
    } else if (!settings_json["shaders"].is_array()) {
        throw std::logic_error("[settings.json] shaders isn't array");
    } else if (settings_json["shaders"].empty()) {
        throw std::logic_error("[settings.json] shaders is empty");
    }

    for (auto &iter : settings_json["shaders"]) {
        if (!iter.is_string()) {
            throw std::logic_error("[settings.json] shaders contains non-string object");
        }

        auto shader_name = iter.get<std::string>();
        shaders.try_emplace(shader_name, shader_name);
    }

    glClearColor(0.0f, 0.4f, 0.75f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Entry::update() {

}
