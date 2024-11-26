#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Init();

	// Utility functions
	std::string LoadShaderSrc(const char* filePath);
	GLuint CompileShader(const char* filePath, GLenum type);

	// Uniform functions
	void SetMat4(const std::string& name, glm::mat4 val);
	void SetInt(const std::string& name, int val);
	void SetFloat(const std::string& name, float val);
};

#endif

