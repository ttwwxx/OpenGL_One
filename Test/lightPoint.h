#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>
class lightPoint
{
public:
	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	lightPoint(glm::vec3 position, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f));
	//Ë¥¼õÏµÊý
	float constant;
	float linear;
	float quaratic;
};

