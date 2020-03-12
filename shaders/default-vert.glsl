#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_color;

out vec2 vert_uv;
out vec4 vert_color;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(in_position, 1.0f);

    vert_uv = in_uv;
    vert_color = in_color;
}
