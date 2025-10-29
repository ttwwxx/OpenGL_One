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
	sampler2D emission;
	float shininess;
};
struct Light
{
	vec3 Color;
	vec3 Position;
	vec3 Direction;
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
	vec3 lightDir = normalize(light.Direction);
	vec3 reflectDir = reflect(-lightDir,norm);
	vec3 cameraDir = normalize(cameraPos - worldPos);

	//specular
	float spec =pow( max(dot(reflectDir, cameraDir),0), material.shininess);
	vec3 color1 = vec3(0.0, 0.0, 1.0); 
	vec3 color2 = vec3(1.0, 0.0, 0.0); 
	vec3 color3 = vec3(0.0, 1.0, 0.0); 
	vec3 specColor = mix(color1, color2,color3) * texture(material.specular, TexCoords).rgb;

	vec3 specular = specColor *  spec * light.Color;
	
	vec3 texColor = texture(material.diffuse, TexCoords).rgb;
	//emission
	vec3 emission = texture(material.emission,TexCoords).rgb;
		//ambient环境光
	vec3 ambient = light.Color * ambientColor * texColor; 
	//diffuse
	float diff = max(dot(lightDir, norm), 0); 
	vec3 diffuse = diff * texColor * light.Color;
	//FragColor = vec4(final,1.0f);
	//FragColor = vec4(texColor, 1.0f);
	vec3 final = ambient + diffuse + specular + emission;
	FragColor = vec4(final, 1.0); // 只显示纹理
};