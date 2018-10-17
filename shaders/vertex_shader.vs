#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 outputColor;

uniform vec3 offset_left;

void main()
{
	gl_Position = vec4(position.x + offset_left.x, position.y, position.z, 1.0);
	outputColor = color;
}