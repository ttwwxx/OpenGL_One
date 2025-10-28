#pragma once
#include"Shader.h"
class Light
{
public:
	Light(Shader *myShader,glm::vec3 lightColor,glm::vec3 lightPosition);
	Shader* shader;
	glm::vec3 Color;
	glm::vec3 Position;


};

