#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>

class lightSpot
{
public:
	lightSpot(glm::vec3 position, glm::vec3 angels, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void UpdateDirection();
	glm::vec3 Position;
	glm::vec3 Angles;
	glm::vec3 Color;
	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);
	float cosInnerphy = 0.9f;
	float cosOutphy = 0.5f;
};

