#pragma once
#include"Shader.h"

class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* myShader,unsigned int myDiffuse, glm::vec3 mySpecular, glm::vec3 myAmbient, float myShininess);
};

