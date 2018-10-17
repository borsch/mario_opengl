#include "shader.h"

Shader::Shader(std::string& vertex_path, std::string& fragment_path)
{
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	v_shader_file.exceptions(std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::badbit);
	try
	{
		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream v_shader_stream, f_shader_stream;

		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();

		v_shader_file.close();
		f_shader_file.close();

		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	GLuint vertex = compile_shader(vertex_code, GL_VERTEX_SHADER);
	GLuint fragment = compile_shader(fragment_code, GL_FRAGMENT_SHADER);

	this->_program = glCreateProgram();
	glAttachShader(this->_program, vertex);
	glAttachShader(this->_program, fragment);
	glLinkProgram(this->_program);

	GLint success;
	GLchar info_logs[512];

	glGetProgramiv(this->_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->_program, 512, NULL, info_logs);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED[" << info_logs  << ']' << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

GLuint Shader::compile_shader(std::string& source, GLenum shader_type)
{
	const GLchar* shader_code = source.c_str();

	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &shader_code, NULL);
	glCompileShader(shader_id);

	GLint success;
	GLchar info_logs[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, info_logs);
		std::cout << "ERROR::SHADER::" << shader_type << "::COMPILATION_FAILED[" << info_logs << ']' << std::endl;
	}

	return shader_id;
}

void Shader::use() const 
{ 
	glUseProgram(this->_program);
}