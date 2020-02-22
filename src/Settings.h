//
// Created by unkorunk on 13.02.2020.
//

#ifndef BLANK_GAME_SETTINGS_H
#define BLANK_GAME_SETTINGS_H

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


#endif //BLANK_GAME_SETTINGS_H
