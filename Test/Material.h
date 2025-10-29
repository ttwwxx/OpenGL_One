#pragma once
#include"Shader.h"

class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	unsigned int specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* myShader,unsigned int myDiffuse, unsigned int mySpecular, glm::vec3 myAmbient, float myShininess);
};

