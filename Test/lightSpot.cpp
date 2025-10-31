#include "lightSpot.h"

lightSpot::lightSpot(glm::vec3 position, glm::vec3 angels, glm::vec3 diffuse, glm::vec3 ambient):
		Position(position),
		Angles(angels),
		Diffuse(diffuse)
{
	UpdateDirection();
}
void lightSpot::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);
	Direction = -1.0f * Direction;
}