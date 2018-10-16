#include "includes.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool is_shader_valid(const GLuint& shader_id);
GLuint create_vao_triangle(const GLfloat* vertices, GLuint array_lenght);

int main()
{
	glfwInit();
	C_OPEN_GL_VERSION(3, 3);
	GLFWwindow* window = C_GLFW_WINDOW_INIT(800, 600, "Mario");
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	const GLfloat vertices1[] = {
	 0.5f,  0.5f, 0.0f,  // Верхний правый угол
	 0.5f, -0.5f, 0.0f,  // Нижний правый угол
	-0.5f, -0.5f, 0.0f,  // Нижний левый угол
	};

	GLuint vao1_id = create_vao_triangle(vertices1, sizeof(vertices1));
	
	const GLfloat vertices2[] = {
		-0.5f,  0.5f, 0.0f, // TL
		0.5f, 0.5f, 0.0f,  // Нижний правый угол
		-0.5f, -0.5f, 0.0f,  // TR
	};

	GLuint vao2_id = create_vao_triangle(vertices2, sizeof(vertices2));


	const GLchar* vertex_shader_source = "#version 330 core \n\
									layout(location = 0) in vec3 position; \
									void main() \
									{ \
										gl_Position = vec4(position.x, position.y, position.z, 1.0); \
									}";

	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader_id);

	const GLchar* fragment_stader_source = "#version 330 core \n\
									out vec4 color; \
									void main() \
									{ \
										color = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
									}";

	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_stader_source, NULL);
	glCompileShader(fragment_shader_id);

	GLuint shader_program_id = glCreateProgram();
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	glLinkProgram(shader_program_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program_id);
		glBindVertexArray(vao2_id);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao1_id);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vao1_id);
	glDeleteVertexArrays(1, &vao2_id);
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

bool is_shader_valid(const GLuint& shader_id)
{
	GLint success;
	GLchar logs[512];

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, logs);

		std::cerr << logs << std::endl;

		return false;
	}

	return true;
}

GLuint create_vao_triangle(const GLfloat* vertices, GLuint array_lenght)
{
	GLuint vao_id, vbo_id;
	glGenVertexArrays(1, &vao_id);
	glGenBuffers(1, &vbo_id);

	// start configure whole VAO
	glBindVertexArray(vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, array_lenght, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// end configure whole vao
	glBindVertexArray(0);

	return vao_id;
}