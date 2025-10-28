#include <glad/glad.h>      // OpenGL 函数加载器（必须在 GLFW 之前）
#include <GLFW/glfw3.h> 
#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>

/*std::ifstream vertexFile;std::ifstream fragmentFile;*/
 using namespace std;//就可以省去std：：但是可能会自己的命名会冲突
 
//命名空间：：函数名
Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit |ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
		
			throw exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		//顶点着色器1
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		//片元着色器
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
		printf(vertexSource);
		printf(fragmentSource);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}
void Shader::use() {
	glUseProgram(ID);
}
void Shader::checkCompileErrors(unsigned int ID, std::string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") 
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "shader compile error:" << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program compile error:" << infoLog << endl;
		}
	}

}
//void Shader::setFloat(const std::string &name,float value) 
//{
//	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//}