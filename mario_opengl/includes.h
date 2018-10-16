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

#endif