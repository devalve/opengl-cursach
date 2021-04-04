#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float firstTriangle[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.0f,  1.0f, 0.0f
};
float secondTriangle[] = {
	 -0.2f,  -0.2f, 0.0f,
	-0.5f, -0.7f, 0.0f,
	 0.5f, -0.7f, 0.0f
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(1920, 1080, "testing", NULL, NULL);

	if (win == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	int vertexShader = glCreateShader(GL_VERTEX_SHADER),
		orangeFragShader = glCreateShader(GL_FRAGMENT_SHADER),
		yellowFragShader = glCreateShader(GL_FRAGMENT_SHADER),
		orangeShaderProg = glCreateProgram(),
		yellowShaderProg = glCreateProgram();

	unsigned int VBO[2], VAO[2];

	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);


	//первый треугольник настройки
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	/*    Аргумент №1: Указываем, какой атрибут вершины мы хотим настроить. Помните, что мы указали расположение позиции вершинного атрибута в вершинном шейдере при помощи layout (location = 0). Благодаря этому, местоположение вершинного атрибута устанавливается в 0, и, поскольку мы хотим передать данные в этот атрибут вершины, мы передаем в качестве параметра значение 0.

   Аргумент №2: Определяем размер вершинного атрибута. Он имеет тип vec3, поэтому состоит из 3-х значений.

   Аргумент №3: Указываем тип данных GL_FLOAT (т.к. vec* в GLSL состоит из значений типа с плавающей точкой).

   Аргумент №4: Указываем, хотим ли мы, чтобы наши данные были нормализованы. Если мы вводим целочисленные типы данных (int, byte) и установили для них значение GL_TRUE, то целочисленные unsigned данные приводятся к 0 (или к -1 для типов данных signed) и к 1 при преобразовании в тип float. Это не имеет отношения к нашему примеру, поэтому мы оставим значение данного аргумента как GL_FALSE.

   Аргумент №5: Известен как шаг (англ. «stride») и говорит нам о пространстве между последовательными атрибутами вершин. Поскольку следующий набор данных местоположения вершины находится на расстоянии 3*sizeof(float), то указываем это значение как шаг. Обратите внимание, поскольку мы знаем, что массив плотно упакован (нет никакого пространства между следующим значением атрибута вершины), мы могли бы также указать величину шага как 0, чтобы позволить OpenGL самому определить шаг (это работает только тогда, когда значения плотно упакованы). Всякий раз, когда мы имеем дело с большим количеством вершинных атрибутов, нужно тщательно определить расстояние между каждым атрибутом (примеры подобных случаев мы рассмотрим несколько позже).
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);



	//второй треугольник настройки
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	const char
		* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0",

		* orangeFragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0",

		* yellowFragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 1.0f, 0.0f, 0.0f); \n"
		"}\n\0";

	//вершинный шейдер
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//фрагментный шейдер(orange)
	glShaderSource(orangeFragShader, 1, &orangeFragShaderSource, nullptr);
	glCompileShader(orangeFragShader);

	//фрагментный шейдер(yellow)
	glShaderSource(yellowFragShader, 1, &yellowFragShaderSource, nullptr);
	glCompileShader(yellowFragShader);

	//соединение шейдеров в одну программу(orange)
	glAttachShader(orangeShaderProg, vertexShader);
	glAttachShader(orangeShaderProg, orangeFragShader);
	glLinkProgram(orangeShaderProg);


	//соединение шейдеров в одну программу(yellow)
	glAttachShader(yellowShaderProg, vertexShader);
	glAttachShader(yellowShaderProg, yellowFragShader);
	glLinkProgram(yellowShaderProg);

	glDeleteShader(vertexShader);
	glDeleteShader(orangeFragShader);

	/*ГЛАВНЫЙ ЦИКЛ ОТРИСОВКИ*/
	while (!glfwWindowShouldClose(win)) {

		processInput(win);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*РИСОВАТЬ ТУТ*/
		glUseProgram(orangeShaderProg);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(yellowShaderProg);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	glfwTerminate();
	return 0;
}




void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}