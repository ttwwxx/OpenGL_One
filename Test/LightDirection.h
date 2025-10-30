#pragma once

#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
/*struct LightDiractional
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
*/

class LightDirection
{
public:
	
	LightDirection(
		glm::vec3 ambient,
		glm::vec3 specular,
		glm::vec3 direction = glm::vec3(0.2f, 1.0f, 0.3f),
		glm::vec3 diffuse =  glm::vec3(0.4f, 0.4f, 0.4f)
		);
	void UpdateDirection();
	glm::vec3 Direction;
	glm::vec3 Ambient;
	glm::vec3 Specular;
	glm::vec3 Diffuse ;

	
};


