#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
//uniform sampler2D mainTexture;
//uniform sampler2D mixTexture;

in vec3 vertexPos;
in vec3 worldPos;
in vec3 Normal;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light
{
	vec3 Color;
	vec3 Position;
};

uniform Material material;
uniform Light light;

uniform vec3 emission;
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 cameraPos;


out vec4 FragColor;
void main()
{
	//ambient
	vec3 ambient = material.ambient * ambientColor ;
	//º∆À„∑ΩœÚ
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - worldPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	vec3 cameraDir = normalize(cameraPos - worldPos);

	//specular
	float spec =pow( max(dot(reflectDir, cameraDir),0), material.shininess);
	vec3 specular = material.specular * spec * light.Color;
	//diffuse
	

	vec3 diffuse = max( dot (lightDir, norm), 0.0f) * light.Color  * material.diffuse * emission;
	
	vec3 final = ambient + diffuse + specular;
	FragColor = vec4(final,1.0f);
};