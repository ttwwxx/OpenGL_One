#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
//uniform sampler2D mainTexture;
//uniform sampler2D mixTexture;

in vec3 vertexPos;
in vec3 worldPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material{
	//vec3 ambient;
	//vec3 diffuse;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
struct Light
{
	vec3 Color;
	vec3 Position;
};

uniform Material material;
uniform Light light;

//uniform vec3 emission;
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 cameraPos;


out vec4 FragColor;
void main()
{

	//计算方向
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - worldPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	vec3 cameraDir = normalize(cameraPos - worldPos);

	//specular
	float spec =pow( max(dot(reflectDir, cameraDir),0), material.shininess);
	vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.Color;
	//diffuse
	vec3 diffuse = texture(material.diffuse, TexCoords).rgb * light.Color;
		//ambient环境光
	vec3 ambient = light.Color * ambientColor ;
	vec3 final = ambient + diffuse + specular;
	vec3 texColor = texture(material.diffuse, TexCoords).rgb;
	//FragColor = vec4(final,1.0f);
	//FragColor = vec4(texColor, 1.0f);
	FragColor = vec4(final, 1.0); // 只显示纹理
};