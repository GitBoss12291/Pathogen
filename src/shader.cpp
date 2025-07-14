// This closely follows the implementation from https://learnopengl.com/Getting-started/Shaders but modified to fit the project, credit goes to Joey de Vries
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "shader.hpp"

namespace pathogen
{
	enum class CompileType
	{
		Program = 0,
		Vertex, 
		Fragment
	};

	void compileSuccess(unsigned int checkObj, CompileType type)
	{
		int success;
		char infoLog[512];

		switch (type)
		{
			case CompileType::Program:
				glGetProgramiv(checkObj, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(checkObj, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
				}
				break;
			case CompileType::Vertex:
				glGetShaderiv(checkObj, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(checkObj, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
				}
				break;
			case CompileType::Fragment:
				glGetShaderiv(checkObj, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(checkObj, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
				}
				break;
		}
	}

	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		} catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOTSUCCESSFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		compileSuccess(vertex, CompileType::Vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		compileSuccess(fragment, CompileType::Fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		compileSuccess(ID, CompileType::Program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::use()
	{
		glUseProgram(ID);
	}

	void Shader::genTexture(unsigned int& texture)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
}
