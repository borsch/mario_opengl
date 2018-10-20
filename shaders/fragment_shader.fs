#version 330 core

out vec4 color;
									
in vec3 outputColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D outTexture2;
									
void main()
{
	color = mix(texture(ourTexture1, TexCoord), texture(outTexture2, TexCoord), 0.2);
}