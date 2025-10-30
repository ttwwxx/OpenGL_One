#include "LightDirection.h"

LightDirection::LightDirection(glm::vec3 ambient, glm::vec3 specular, glm::vec3 direction, glm::vec3 diffuse):
	Direction(direction),
	Ambient(ambient),
	Specular(specular),
	Diffuse(diffuse)
{
	UpdateDirection();
}
void LightDirection::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	/*Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);*/
	Direction = -1.0f * Direction;
}