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
#include "IO/Keyboard.h"
#include "IO/Mouse.h"
// Global variables
float alpha = 0.5f;
bool rotation = false;
unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
float x, y, z;
glm::mat4 movement = glm::mat4(1.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

//void testInput(GLFWwindow* window, GLuint texture1, GLuint texture2);
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLEngine", NULL, NULL);
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
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Keyboard
	glfwSetKeyCallback(window, Keyboard::KeyCallback);

	// Mouse
	glfwSetCursorPosCallback(window, Mouse::CursorPositionCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::MouseWheelCallback);

	glEnable(GL_DEPTH_TEST);

	// Shaders
	Shader shader = Shader("Assets/vertex_core.glsl", "Assets/fragment_core.glsl");
	//Shader shader2 = Shader("Assets/vertex_core.glsl", "Assets/fragment_core2.glsl");
	// Vertex array

	// TRIANGLE
	//float vertices[] = {
	//	// Positions				// Colors			TexCoord
	//	//-0.25f, -0.5f, 0.0f,		1.0f, 1.0f, 0.5f,
	//	//0.15f, 0.0f, 0.0f,		0.5f, 1.0f, 0.75f,
	//	//0.0f, 0.5f, 0.0f,		0.6f, 1.0f, 0.2f,
	//	//0.5f, -0.4f, 0.0f,		1.0f, 0.2f, 1.0f
	//	-0.5f, -0.5f, 0.0f,			1.0f, 1.0f, 0.5f,	0.0f, 0.0f, // 0
	//	-0.5f, 0.5f, 0.0f,			0.5f, 1.0f, 0.75f,	0.0f, 1.f, // 1
	//	0.5f, -0.5f, 0.0f,			0.6f, 1.0f, 0.2f,	1.0f, 0.0f, // 2
	//	0.5f, 0.5f, 0.0f,			1.0f, 0.2f, 1.0f,	1.0f, 1.0f	// 3

	//};
	// CUBE
	float vertices[] = {
	// Position			  TexCoord		Colours
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
										
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
										
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	
										
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f	
	};
	//unsigned int indices[] = {
	//	0 , 1 , 2, // 1st triangle
	//	3 ,	1 ,	2 // 2nd triangle
	//};
	// VAO , VBO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions

	// Set attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Textures
	GLuint texture1, texture2;

	glGenTextures(1,&texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x coordinates of texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y coordinates of texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Load image
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Assets/img.jpg", &width, &height, &nChannels, 0);

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

	data = stbi_load("Assets/img3.jpg", &width, &height, &nChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);

	//

	shader.Init();

	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);


	// Transformation matrix
	x = 0.0f;
	y = 0.0f;
	z = 3.0f;

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process Input
		processInput(window);
		//testInput(window, shader, alpha);
		// Render
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Draw shapes
		glBindVertexArray(VAO);

		// Create transformation for screen

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(.5f));
		view = glm::translate(view, glm::vec3(-x, -y, -z));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);

		shader.Init();
		shader.SetFloat("alpha", alpha);
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		glBindVertexArray(0);
		
		// Sends new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Adjusting!, New Width: " << width << ", New Height: " << height << std::endl;
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void processInput(GLFWwindow* window)
{
	if (Keyboard::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window,true);
	}
	if (Keyboard::Key(GLFW_KEY_UP))
	{
		std::cout << "UP PRESSED" << std::endl;
		alpha += 0.05f;
		if (alpha > 1.0f)
			alpha = 1.0f;
	}
	if (Keyboard::Key(GLFW_KEY_DOWN))
	{
		std::cout << "DOWN PRESSED" << std::endl;
		alpha -= 0.05f;
		if (alpha < 0.0f)
			alpha = 0.f;
	}
	if (Keyboard::IsKeyDown(GLFW_KEY_R))
	{
		std::cout << "Rotate" << std::endl;
		rotation = !rotation;
	}


	if (Keyboard::Key(GLFW_KEY_W))
	{
		z -= 0.1f;
	}
	if (Keyboard::Key(GLFW_KEY_S))
	{
		z += 0.1f;
	}
	if (Keyboard::Key(GLFW_KEY_A))
	{
		x -= 0.1f;
	}
	if (Keyboard::Key(GLFW_KEY_D))
	{
		x += 0.1f;
	}
}