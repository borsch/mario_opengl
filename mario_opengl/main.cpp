#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define C_OPEN_GL_VERSION(major, minor) glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
#define C_GLFW_WINDOW_INIT(width, height, name) glfwCreateWindow(width, height, name, nullptr, nullptr)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	glfwInit();
	C_OPEN_GL_VERSION(3, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = C_GLFW_WINDOW_INIT(800, 600, "Mario");
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSetKeyCallback(window, key_callback);
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}