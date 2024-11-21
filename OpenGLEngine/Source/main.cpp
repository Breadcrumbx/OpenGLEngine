#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main()
{
	// Test
	std::cout << "Hello World!" << std::endl;

	int success;
	char infoLog[512];

	// Initialise GLFW
	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLEngine", NULL, NULL);
	// Check if window is created or not
	if (window == NULL)
	{
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set current state machine / context to our window
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Tells OpenGL the size of the rendering window so it knows how to display data / coordinates with respect to the window
	glViewport(0, 0, 800, 600);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shaders
	Shader shader = Shader("Assets/vertex_core.glsl", "Assets/fragment_core.glsl");
	Shader shader2 = Shader("Assets/vertex_core.glsl", "Assets/fragment_core2.glsl");
	// Vertex array
	float vertices[] = {
		// Positions			// colors
		-0.25f, -0.5f, 0.0f,		1.0f, 1.0f, 0.5f,
		0.15f, 0.0f, 0.0f,		0.5f, 1.0f, 0.75f,
		0.0f, 0.5f, 0.0f,		0.6f, 1.0f, 0.2f,
		0.5f, -0.4f, 0.0f,		1.0f, 0.2f, 1.0f
	};

	unsigned int indices[] = {
		0 , 1 , 2, // 1st triangle
		3 ,	1 ,	2 // 2nd triangle
	};
	// VAO , VBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions

	// Set attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Transformation matrix
	glm::mat4 transform = glm::mat4(1.0f); // Identity 4x4 matrix
	transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.Init();
	shader.SetMat4("transform", transform);

	glm::mat4 transform2 = glm::mat4(1.0f);
	transform2 = glm::scale(transform2, glm::vec3(1.5f));
	transform2 = glm::rotate(transform2, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shader2.Init();
	shader2.SetMat4("transform", transform);
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process Input
		processInput(window);

		// Render
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		transform = glm::rotate(transform, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.Init();
		shader.SetMat4("transform", transform);

		// Draw shapes
		glBindVertexArray(VAO);

		// First triangle
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		transform2 = glm::rotate(transform2, glm::radians((float)glfwGetTime() / -100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader2.Init();
		shader2.SetMat4("transform", transform2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

		// Second triangle
		//glUseProgram(shaderPrograms[1]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

		glBindVertexArray(0);

		// Sends new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Adjusting!, New Width: " << width << ", New Height: " << height << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}