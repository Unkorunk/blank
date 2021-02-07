//
// Created by unkorunk on 27.01.2020.
//

#include "Shader.h"

Shader::Shader(const std::string& shader_name) {
    program = glCreateProgram();

    std::vector<GLuint> shaders_ids;

    const std::string dir_shaders = "./assets/shaders";

    const std::vector<std::pair<GLuint, std::string>> shader_types{
            {GL_VERTEX_SHADER,          "vert"},
            {GL_TESS_CONTROL_SHADER,    "cont"},
            {GL_TESS_EVALUATION_SHADER, "eval"},
            {GL_GEOMETRY_SHADER,        "geom"},
            {GL_FRAGMENT_SHADER,        "frag"},
            {GL_COMPUTE_SHADER,         "comp"}
    };

    for (auto& type : shader_types) {
        std::ifstream ifs(dir_shaders + "/" + shader_name + "-" + type.second + ".glsl");
        if (ifs.is_open()) {
            shaders_ids.push_back(glCreateShader(type.first));

            std::string source((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            const GLchar* source_raw = reinterpret_cast<const GLchar*>(source.c_str());
            glShaderSource(shaders_ids.back(), 1, &source_raw, nullptr);

            glCompileShader(shaders_ids.back());

            GLint is_compiled = 0;
            glGetShaderiv(shaders_ids.back(), GL_COMPILE_STATUS, &is_compiled);
            if (is_compiled == GL_FALSE) {
                GLint max_length = 0;
                glGetShaderiv(shaders_ids.back(), GL_INFO_LOG_LENGTH, &max_length);

                std::string error_msg(max_length, ' ');
                glGetShaderInfoLog(shaders_ids.back(), max_length, &max_length, error_msg.data());

                glDeleteProgram(program);

                for (GLuint shader_id : shaders_ids) {
                    glDeleteShader(shader_id);
                }

                throw std::logic_error("[Shader] compilation shader with name " + shader_name + "-" + type.second +
                    " finished with error: " + error_msg);
            }

            glAttachShader(program, shaders_ids.back());

            ifs.close();
        }
    }

    if (shaders_ids.empty()) {
        throw std::logic_error("[Shader] not found shaders with name " + shader_name);
    }

    glLinkProgram(program);

    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

        std::string error_msg(max_length, ' ');
        glGetProgramInfoLog(program, max_length, &max_length, error_msg.data());

        glDeleteProgram(program);

        for (GLuint shader_id : shaders_ids) {
            glDeleteShader(shader_id);
        }

        throw std::logic_error("[Shader] link shaders with name " + shader_name +
            " finished with error: " + error_msg);
    }

    for (GLuint shader_id : shaders_ids) {
        glDetachShader(program, shader_id);
    }

    // arrays
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // buffers
    GLint active_attributes;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &active_attributes);
    buffers.resize(active_attributes);
    glGenBuffers(active_attributes, buffers.data());

    // for visual scripting
    GLint active_uniforms;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &active_uniforms);

    std::vector<GLuint> uniform_indices(active_uniforms);
    std::iota(uniform_indices.begin(), uniform_indices.end(), 0);

    std::vector<GLint> uniform_lengths(active_uniforms);
    glGetActiveUniformsiv(program, active_uniforms, uniform_indices.data(), GL_UNIFORM_NAME_LENGTH, uniform_lengths.data());

    std::vector<std::string> uniform_names(active_uniforms);
    for (GLint i = 0; i < active_uniforms; i++) {
        uniform_names[i].assign(uniform_lengths[i], ' ');
        glGetActiveUniformName(program, uniform_indices[i], uniform_lengths[i], nullptr, uniform_names[i].data());
    }

    for (GLint i = 0; i < active_uniforms; i++) {
        std::cout << "[" << uniform_indices[i] << "]: " << uniform_names[i] << std::endl;
    }

}

Shader::~Shader() {
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
    glDeleteProgram(program);
}

void Shader::activate() {
    glUseProgram(program);
    for (GLuint i = 0; i < buffers.size(); i++) {
        glEnableVertexAttribArray(i);
    }
}

void Shader::deactivate() {
    for (GLuint i = 0; i < buffers.size(); i++) {
        glDisableVertexAttribArray(i);
    }
}

void Shader::set(const std::string &uniform, const glm::vec2 &data) {
    GLint location = glGetUniformLocation(program, uniform.c_str());
    glProgramUniform2fv(program, location, 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::vec3 &data) {
    GLint location = glGetUniformLocation(program, uniform.c_str());
    glProgramUniform3fv(program, location, 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::vec4 &data) {
    GLint location = glGetUniformLocation(program, uniform.c_str());
    glProgramUniform4fv(program, location, 1, glm::value_ptr(data));
}

void Shader::set(const std::string &uniform, const glm::ivec2 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform2iv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::ivec3 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform3iv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::ivec4 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform4iv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}

void Shader::set(const std::string &uniform, const glm::uvec2 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform2uiv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::uvec3 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform3uiv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::uvec4 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform4uiv(program, uniform_locations[uniform], 1, glm::value_ptr(data));
}

void Shader::set(const std::string &uniform, const glm::mat2 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniformMatrix2fv(program, uniform_locations[uniform], 1, GL_FALSE, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::mat3 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniformMatrix3fv(program, uniform_locations[uniform], 1, GL_FALSE, glm::value_ptr(data));
}
void Shader::set(const std::string &uniform, const glm::mat4 &data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniformMatrix4fv(program, uniform_locations[uniform], 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::set(const std::string &uniform, GLint data) {
    if (uniform_locations.count(uniform) == 0) {
        uniform_locations[uniform] = glGetUniformLocation(program, uniform.c_str());
    }
    glProgramUniform1i(program, uniform_locations[uniform], data);
}

void Shader::set(GLuint location, GLsizeiptr count_bytes, GLint elements_in_batch, GLfloat *data) {
    glBindBuffer(GL_ARRAY_BUFFER, buffers[location]);
    glBufferData(GL_ARRAY_BUFFER, count_bytes, data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, elements_in_batch, GL_FLOAT, GL_FALSE, 0, nullptr);
}
