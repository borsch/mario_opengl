#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>;

class Shader
{
private: 
	GLuint _program;

	GLuint compile_shader(std::string& source, GLenum shader_type);
public:
	Shader(std::string& vertex_path, std::string& fragment_path);

	void use() const;
};

#endif