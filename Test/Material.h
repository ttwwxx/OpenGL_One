#pragma once
#include"Shader.h"

class Material
{
public:
	Shader* shader;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* myShader, glm::vec3 myDiffuse, glm::vec3 mySpecular, glm::vec3 myAmbient, float myShininess);
};

