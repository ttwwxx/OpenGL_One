#include "lightPoint.h"

lightPoint::lightPoint(glm::vec3 position,glm::vec3 angels ,glm::vec3 color) :
	Position(position),
	Color(color),
	Angels(angels)
{

	constant = 1.0f;
	linear = 0.09f;
	quaratic = 0.032f;
}
