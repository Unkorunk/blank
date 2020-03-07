//
// Created by unkorunk on 03.03.2020.
//

#pragma once

#include <map>
#include <string>

#include "IManager.h"
#include "Shader.h"
#include "Settings.h"

class ResourceManager : public IManager {
public:
    explicit ResourceManager(Blank *blank) : IManager(blank) {}
    virtual ~ResourceManager() = default;

    void start() override {
        for (auto& shader_name : Settings::getInstance().getShaders()) {
            shaders.try_emplace(shader_name, new Shader(shader_name));
        }
    }

    Shader *getShader(const std::string& shader_name) const {
        return shaders.at(shader_name).get();
    }

    Shader *getDefaultShader() const {
        return shaders.at(Settings::getInstance().get<std::string>("default_shader")).get();
    }

private:
    std::map<std::string, std::unique_ptr<Shader>> shaders;

};
