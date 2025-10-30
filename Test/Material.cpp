#include "Material.h"


Material::Material(Shader* myShader, unsigned int myDiffuse, unsigned int mySpecular, float myShininess):
	shader(myShader),
	diffuse(myDiffuse),
	specular(mySpecular),
	shininess(myShininess)
{

}
