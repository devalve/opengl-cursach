#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include <glad/glad.h>
#include <glm.hpp>

using namespace std;

class Shader
{
public:
	unsigned int ID;
	// онструктор генерирует шейдер на лету
	Shader(const char* vertPath, const char* fragPath) {
		string vertCode, fragCode;
		ifstream vShaderFile, fShaderFile;

		try
		{
			vShaderFile.open(vertPath);
			fShaderFile.open(fragPath);

			stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertCode = vShaderStream.str();
			fragCode = fShaderStream.str();

		}
		catch (const ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}
		const char* vShaderCode = vertCode.c_str(), * fShaderCode = fragCode.c_str();



		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER),
			fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);


		glDeleteShader(vertex);
		glDeleteShader(fragment);
	};


	void use() {
		glUseProgram(ID);
	};
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:

};

