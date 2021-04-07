#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include <glad/glad.h>
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

private:
};

