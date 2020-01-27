//
// Created by unkorunk on 27.01.2020.
//

#ifndef BLANK_SHADER_H
#define BLANK_SHADER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <exception>

#include <GL/glew.h>

class Shader {
public:
    explicit Shader(const std::string& shader_name);
    ~Shader();

private:
    GLuint program_id;
};


#endif //BLANK_SHADER_H
