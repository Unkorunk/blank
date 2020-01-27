//
// Created by unkorunk on 27.01.2020.
//

#include "Shader.h"

Shader::Shader(const std::string& shader_name) {
    program_id = glCreateProgram();

    std::vector<GLuint> shaders_ids;

    const std::string dir_shaders = "./shaders";

    const std::vector<std::pair<GLuint, std::string>> shader_types{
            {GL_VERTEX_SHADER,          "vert"},
            {GL_TESS_CONTROL_SHADER,    "cont"},
            {GL_TESS_EVALUATION_SHADER, "eval"},
            {GL_GEOMETRY_SHADER,        "geom"},
            {GL_FRAGMENT_SHADER,        "frag"},
            {GL_COMPUTE_SHADER,         "comp"}
    };

    for (auto &type : shader_types) {
        std::ifstream ifs(dir_shaders + "/" + shader_name + "-" + type.second + ".glsl");
        if (ifs.is_open()) {
            shaders_ids.push_back(glCreateShader(type.first));

            std::string source((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            const GLchar *source_raw = reinterpret_cast<const GLchar *>(source.c_str());
            glShaderSource(shaders_ids.back(), 1, &source_raw, nullptr);

            glCompileShader(shaders_ids.back());

            GLint is_compiled = 0;
            glGetShaderiv(shaders_ids.back(), GL_COMPILE_STATUS, &is_compiled);
            if (is_compiled == GL_FALSE) {
                GLint max_length = 0;
                glGetShaderiv(shaders_ids.back(), GL_INFO_LOG_LENGTH, &max_length);

                std::string error_msg(max_length, ' ');
                glGetShaderInfoLog(shaders_ids.back(), max_length, &max_length, error_msg.data());

                glDeleteProgram(program_id);

                for (GLuint shader_id : shaders_ids) {
                    glDeleteShader(shader_id);
                }

                throw std::logic_error("[Shader] compilation shader with name " + shader_name + "-" + type.second +
                                       " finished with error: " + error_msg);
            }

            glAttachShader(program_id, shaders_ids.back());

            ifs.close();
        }
    }

    if (shaders_ids.empty()) {
        throw std::logic_error("[Shader] not found shaders with name " + shader_name);
    }

    glLinkProgram(program_id);

    GLint is_linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);

        std::string error_msg(max_length, ' ');
        glGetProgramInfoLog(program_id, max_length, &max_length, error_msg.data());

        glDeleteProgram(program_id);

        for (GLuint shader_id : shaders_ids) {
            glDeleteShader(shader_id);
        }

        throw std::logic_error("[Shader] link shaders with name " + shader_name +
                               " finished with error: " + error_msg);
    }

    for (GLuint shader_id : shaders_ids) {
        glDetachShader(program_id, shader_id);
    }

}

Shader::~Shader() {
    glDeleteProgram(program_id);
}
