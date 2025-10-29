#include "Material.h"


Material::Material(Shader* myShader, unsigned int myDiffuse, 
	unsigned int mySpecular, unsigned int myEmission, 
	glm::vec3 myAmbient, float myShininess):
	shader(myShader),
	diffuse(myDiffuse),
	specular(mySpecular),
	emission(myEmission),
	ambient(myAmbient),
	shininess(myShininess)
{

}
