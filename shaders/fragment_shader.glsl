#version 330 core

out vec4 color;
									
in vec3 outputColor;
									
void main()
{
	color = vec4(outputColor, 1.0);
}