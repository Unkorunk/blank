//
// Created by unkorunk on 13.02.2020.
//

#include "Settings.h"

Settings &Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {
    std::ifstream settings_ifs("./assets/settings.json");
    if (!settings_ifs.is_open()) {
        throw std::logic_error("[settings.json] not found file");
    }

    settings_ifs >> settings_json;
    settings_ifs.close();
}

std::vector<std::string> Settings::getShaders() const {
    std::vector<std::string> shaders;

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
        shaders.push_back(shader_name);
    }

    return shaders;
}
