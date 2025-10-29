#include "LightDirection.h"

LightDirection::LightDirection(glm::vec3 position, glm::vec3 angles, glm::vec3 color):
	Position(position),
	Angles(angles),
	Color(color)			
{
	UpdateDirection();
}
void LightDirection::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);
	Direction = -1.0f * Direction;
}