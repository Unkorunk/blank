//
// Created by unkorunk on 27.01.2020.
//

#ifndef BLANK_SHADER_H
#define BLANK_SHADER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <exception>
#include <memory>
#include <functional>
#include <map>
#include <numeric>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    explicit Shader(const std::string &shader_name);
    ~Shader();

    void activate();
    void deactivate();

    // Attributes
    void set(GLuint location, GLsizeiptr count_bytes, GLint elements_in_batch, GLfloat* data);

    // Uniforms
    void set(const std::string &uniform, const glm::vec2 &data);
    void set(const std::string &uniform, const glm::vec3 &data);
    void set(const std::string &uniform, const glm::vec4 &data);

    void set(const std::string &uniform, const glm::ivec2 &data);
    void set(const std::string &uniform, const glm::ivec3 &data);
    void set(const std::string &uniform, const glm::ivec4 &data);

    void set(const std::string &uniform, const glm::uvec2 &data);
    void set(const std::string &uniform, const glm::uvec3 &data);
    void set(const std::string &uniform, const glm::uvec4 &data);

    void set(const std::string &uniform, const glm::mat2 &data);
    void set(const std::string &uniform, const glm::mat3 &data);
    void set(const std::string &uniform, const glm::mat4 &data);

    void set(const std::string &uniform, GLint data);

private:
    GLuint program;
    GLuint vertex_array;
    std::vector<GLuint> buffers;
    std::map<std::string, GLint> uniform_locations;

};

#endif //BLANK_SHADER_H
