#version 330 core

in vec2 vert_uv;
in vec4 vert_color;

out vec4 color;

uniform bool use_texture;
uniform sampler2D m_sampler;

void main() {
    if (use_texture) {
        color = texture(m_sampler, vert_uv).rgba;
    } else {
        color = vert_color;
    }
}
