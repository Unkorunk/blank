#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_color;

out vec2 vert_uv;
out vec4 vert_color;

void main() {
    gl_Position.xyz = in_position;
    gl_Position.w = 1.0;

    vert_uv = in_uv;
    vert_color = in_color;
}
