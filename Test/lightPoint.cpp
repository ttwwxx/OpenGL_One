#include "lightPoint.h"

lightPoint::lightPoint(glm::vec3 position, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse) :
	position(position),
	ambient(ambient),
	specular(specular),
	diffuse(diffuse)
{

	constant = 1.0f;
	linear = 0.09f;
	quaratic = 0.032f;
}
