#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>
class lightPoint
{
public:
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec3 Angels;
	lightPoint(glm::vec3 position, glm::vec3 angels, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	//Ë¥¼õÏµÊý
	float constant;
	float linear;
	float quaratic;
};

