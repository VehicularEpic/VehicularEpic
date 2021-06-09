#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TexturePosition;

out vec2 Coordinates;

void main() {
	gl_Position = vec4(Position.xy, 0.0, 1.0);

	Coordinates = TexturePosition;
}
