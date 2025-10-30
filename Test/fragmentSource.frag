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
struct LightPoint
{
//点光源的衰减系数
	float Constant;
	float Linear;
	float Quaratic;
};
struct LightSpot
{
	float cosInnerphy;
	float cosOutphy;
};
uniform Material material;
uniform Light light;
uniform LightPoint lightpoint;
uniform LightSpot lights;
//uniform vec3 emission;
uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
void main()
{
	vec3 final;
	float dist = length(light.Position - worldPos);
	//点光源衰减计算
	float attenuation = 1.0 / (lightpoint.Constant + lightpoint.Linear * dist + lightpoint.Quaratic * (dist * dist));

	//计算方向
	vec3 norm = normalize(Normal);
	//平行光方向vec3 lightDir = normalize(light.Direction);
	//点光源方向
	vec3 lightDir = normalize(light.Position - worldPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	vec3 cameraDir = normalize(cameraPos - worldPos);

	//specular
	float spec =pow( max(dot(reflectDir, cameraDir),0), material.shininess);
	vec3 color1 = vec3(0.0, 0.0, 1.0); 
	vec3 color2 = vec3(1.0, 0.0, 0.0); 
	vec3 color3 = vec3(0.0, 1.0, 0.0); 
	vec3 specColor =texture(material.specular, TexCoords).rgb;

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
	//聚光灯设置
	float cosTheta = dot(normalize(worldPos - light.Position), -1 * light.Direction);
	float spotStrength;
	if(cosTheta > lights.cosInnerphy)
	{
		spotStrength = 1.0f;
	}
	else if(cosTheta > lights.cosOutphy)
	{
		spotStrength = 1.0 -  (cosTheta - lights.cosInnerphy) / (lights.cosOutphy - lights.cosInnerphy); 
	}
	else
	{
		spotStrength = 0.0f;
	}
		final = ambient + (diffuse + specular) * spotStrength;
	
	FragColor = vec4(final, 1.0); // 只显示纹理
};