#version 330 core

in vec2 UV;

out vec4 color;

uniform bool use_texture;
uniform sampler2D m_sampler;

void main() {
    if (use_texture) {
        color = texture(m_sampler, UV).rgba;
    } else {
        color = vec4(1, 0, 0, 1);
    }
}
