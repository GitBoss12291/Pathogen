#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace pathogen
{
	class Shader
	{
		public:
			unsigned int ID;

			Shader(const char* vertexPath, const char* fragmentPath);

			void use();

			void genTexture(unsigned int& texture, const char* texPath);

			void setBool(const std::string& name, bool value) const;
			void setInt(const std::string& name, int value) const;
			void setFloat(const std::string& name, float value) const;
			void setVec2(const std::string& name, const float* value) const;
			void setVec2(const std::string& name, float value1, float value2) const;
			void setVec4(const std::string& name, const float* value) const;
			void setMat4(const std::string& name, const float* value) const;
	};
}

#endif