#pragma once
#include"Shader.h"

class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emission;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* myShader,unsigned int myDiffuse, 
		unsigned int mySpecular, unsigned int myEmission,
		glm::vec3 myAmbient, float myShininess);
};

