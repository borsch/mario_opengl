#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 inTexCoord;

out vec3 outputColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	outputColor = color;

	// flip vertically
	TexCoord = vec2(inTexCoord.x, 1.0 - inTexCoord.y);
}