#ifndef INCLUDES_H
#define INCLUDES_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define C_OPEN_GL_VERSION(major, minor) glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); \
										glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); \
										glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
										glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#define C_GLFW_WINDOW_INIT(width, height, name) glfwCreateWindow(width, height, name, nullptr, nullptr); \
												if (window == nullptr) \
												{ \
													glfwTerminate(); \
													return -1; \
												} \
 
#define C_DEFAULT_VERTEX_SHADER "#version 330 core \n\
									layout(location = 0) in vec3 position; \
									void main() \
									{ \
										gl_Position = vec4(position.x, position.y, position.z, 1.0); \
									}"

#define C_DEFAULT_FRAGMENT_SHADER "#version 330 core \n\
									out vec4 color; \
									void main() \
									{ \
										color = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
									}"

#endif