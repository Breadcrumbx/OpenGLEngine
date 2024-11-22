#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>


#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

void testInput(GLFWwindow* window, GLuint texture1, GLuint texture2);
int main()
{
	// Test
	std::cout << "Hello World!" << std::endl;

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
		// Positions			// colors				TexCoord
		//-0.25f, -0.5f, 0.0f,		1.0f, 1.0f, 0.5f,
		//0.15f, 0.0f, 0.0f,		0.5f, 1.0f, 0.75f,
		//0.0f, 0.5f, 0.0f,		0.6f, 1.0f, 0.2f,
		//0.5f, -0.4f, 0.0f,		1.0f, 0.2f, 1.0f
		-0.5f, -0.5f, 0.0f,			1.0f, 1.0f, 0.5f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,			0.5f, 1.0f, 0.75f,	0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,			0.6f, 1.0f, 0.2f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,			1.0f, 0.2f, 1.0f,	1.0f, 1.0f

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Texture
	GLuint texture1, texture2;

	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x coordinates of texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y coordinates of texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Load image
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Assets/img1.jpg", &width, &height, &nChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	// Frees up the data
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("Assets/img2.png", &width, &height, &nChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);


	shader.Init();

	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);
	// Set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Transformation matrix
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process Input
		processInput(window);

		// Render
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// Draw shapes
		glBindVertexArray(VAO);

		// First triangle
		shader.Init();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//shader2.Init();
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

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

void testInput(GLFWwindow* window, GLuint texture1, GLuint texture2)
{
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
	}
	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
	}
}