#pragma once
#include<string>
#include<glm/glm.hpp>
#include <glad/glad.h>      // OpenGL 函数加载器（必须在 GLFW 之前）
#include <GLFW/glfw3.h> 
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	//void test();

	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;//Shader Program ID

	enum Slot
	{
		DIFFUSE,
		SPECULAR
	};

	//封装Location
	void setBool(const std::string& name, bool value)const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value)const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value)const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string &name, const glm::vec2 &value)const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, const glm::vec3 &value)const
	{
		glUniform3fv(glGetUniformLocation(ID,name.c_str()),1, &value[0]);
	}
	void setVec4(const std::string& name, const glm::vec4& value)const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setMat2(const std::string &name,const glm::mat2 &value)const
	{
		//第三个参数是问是否转置
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE,&value[0][0]);
	}
	void setMat3(const std::string& name, const glm::mat3& value)const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);
	}
	void setMat4(const std::string& name, const glm::mat4& value)const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void use();
private:
	void checkCompileErrors(unsigned int ID, std::string type);
	};

