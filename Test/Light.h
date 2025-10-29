#pragma once
#include"Shader.h"
class Light
{
public:
	Light(Shader *myShader,glm::vec3 lightColor,glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f,1.0f));
	Shader* shader;
	glm::vec3 Color;
	glm::vec3 Position;


};

