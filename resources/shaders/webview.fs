#version 330 core

in vec2 Coordinates;

out vec4 OutputColor;

uniform sampler2D Texture;

void main() {
    OutputColor = texture(Texture, Coordinates);
}
