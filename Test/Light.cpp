#include "Light.h"

Light::Light(Shader* myShader, glm::vec3 lightColor, glm::vec3 lightPosition) :
	shader(myShader)
{
	//lightColor.x = sin(glfwGetTime() * 2.0f);
	//lightColor.y = sin(glfwGetTime() * 0.7f);
	//lightColor.z = sin(glfwGetTime() * 1.3f);
	Color = lightColor;
	Position = lightPosition;


}
