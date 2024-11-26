#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int success;
	char infoLog[512];

	GLuint vertexShader = CompileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	// Creates shader program
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	// Error checking
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Linking error: " << infoLog << std::endl;
	}

	// Clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Init()
{
	glUseProgram(id);
}

std::string Shader::LoadShaderSrc(const char* filePath)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	file.open(filePath);
	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
		std::cout << "Could not open " << filePath << std::endl;

	file.close();

	return ret;
}

GLuint Shader::CompileShader(const char* filePath, GLenum type)
{
	int success;
	char infoLog[512];

	GLuint ret = glCreateShader(type);
	std::string shaderSrc = LoadShaderSrc(filePath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(ret, 1, &shader, NULL);
	glCompileShader(ret);

	// Error checking
	glGetProgramiv(ret, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ret, 512, NULL, infoLog);
		std::cout << "Linking error: " << infoLog << std::endl;
	}

	return ret;
}

void Shader::SetMat4(const std::string& name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::SetInt(const std::string& name, int val)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::SetFloat(const std::string& name, float val)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), val);
}


