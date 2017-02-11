#include "Shader.h"
#include <string>
#include <fstream>
#include <iostream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		std::string line;

		// Open files
		auto vShaderFile = std::ifstream(vertexPath);

		if (!vShaderFile.is_open())
		{
			throw 1;
		}

		while (std::getline(vShaderFile, line))
		{
			vertexCode += line + '\n';
		}
		vShaderFile.close();

		auto fShaderFile = std::ifstream(fragmentPath);

		if (!fShaderFile.is_open())
		{
			throw 2;
		}

		while (std::getline(fShaderFile, line))
		{
			fragmentCode += line + '\n';
		}
		fShaderFile.close();
	}
	catch (int e)
	{
		if (e == 1)
		{
			std::cout << "ERROR::VERTEX_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		else if (e == 2)
		{
			std::cout << "ERROR::FRAGMENT_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		else
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
	}

	auto vShaderCode = vertexCode.c_str();
	auto fShaderCode = fragmentCode.c_str();

	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);

	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() const
{
	glUseProgram(this->Program);
}
