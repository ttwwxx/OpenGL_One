#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material{
	float shininess;
	sampler2D diffuse;
	sampler2D specular;
};
struct LightDiractional
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform LightDiractional lightd;
uniform vec3 cameraPos;

vec3 CaculateLightDiractional(LightDiractional lightd, vec3 normal, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal) * 0.5f + 0.5f ;
	vec3 viewDir = normalize(cameraPos - FragPos);

	vec3 final = CaculateLightDiractional(lightd, normal, viewDir);
	FragColor = vec4(final,1.0);
	 // FragColor = texture(material.diffuse, TexCoords);  
	

}
vec3 CaculateLightDiractional(LightDiractional lightd, vec3 normal, vec3 viewDir)
{
	
	vec3 lightdDir = normalize(-lightd.direction);
	//漫反射计算
	float diff = max(dot(normal, lightdDir),0);
	//镜面光
	vec3 reflecDir = reflect(-lightdDir, normal);
	float spec  = pow(max(dot(reflecDir,viewDir),0), material.shininess);
	//最终颜色计算
	vec3 ambient = lightd.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = diff * vec3(texture(material.diffuse, TexCoords)) * lightd.diffuse;
	vec3 specular = spec * vec3(texture(material.specular, TexCoords)) * lightd.specular;
	vec3 final;
	final = diffuse + ambient + specular;
	
	return final;
}