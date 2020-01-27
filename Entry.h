//
// Created by unkorunk on 26.01.2020.
//

#ifndef BLANK_ENTRY_H
#define BLANK_ENTRY_H

#include <string>
#include <fstream>
#include <exception>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include "Shader.h"

class Entry {
public:
    static Entry &getInstance();

//    Entry &operator=(const Entry &) = delete;
//    Entry(const Entry &) = delete;
//
//    Entry &operator=(Entry &&) = delete;
//    Entry(Entry &&) = delete;

    void awake();
    void start();
    void update();
private:
    using json = nlohmann::json;

    Entry() = default;

    std::map<std::string, Shader> shaders;
};


#endif //BLANK_ENTRY_H
