//
// Created by unkorunk on 13.02.2020.
//

#pragma once

#include <fstream>
#include <exception>
#include <string>

#include <nlohmann/json.hpp>

class Settings {
    using json = nlohmann::json;
public:
    static Settings& getInstance();

    template<typename T>
    T get(const std::string& key) const {
        if (!settings_json.contains(key)) {
            throw std::logic_error("[settings.json] not contains key - " + key);
        }

        return settings_json[key].get<T>();
    }

    std::vector<std::string> getShaders() const;
private:
    Settings();
    json settings_json;
};
