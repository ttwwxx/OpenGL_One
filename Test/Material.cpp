#include "Material.h"


Material::Material(Shader* myShader, unsigned int myDiffuse, unsigned int mySpecular, glm::vec3 myAmbient, float myShininess):
	shader(myShader),
	diffuse(myDiffuse),
	specular(mySpecular),
	ambient(myAmbient),
	shininess(myShininess)
{

}
