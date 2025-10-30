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
//平行光
struct LightDiractional
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//点光源
struct LightPoint
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform LightPoint lightps[NR_POINT_LIGHTS];
uniform LightDiractional lightd;

uniform Material material;
uniform vec3 cameraPos;

vec3 CaculateLightDiractional(LightDiractional lightd, vec3 normal, vec3 viewDir);
vec3 CaculateLightPoint(LightPoint lightp, vec3 normal, vec3 fragPos,vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal) * 0.5f + 0.5f ;
	vec3 viewDir = normalize(cameraPos - FragPos);
	//平行光计算
	vec3 finalLD = CaculateLightDiractional(lightd, normal, viewDir);
	//点光源计算
	vec3 finalLP;
	for(int i = 0; i< NR_POINT_LIGHTS; i++){
		finalLP += CaculateLightPoint(lightps[i], normal,FragPos,viewDir);
	}
	vec3 final = finalLD + finalLP;
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
	vec3 specStrength = pow(texture(material.specular, TexCoords).rgb , vec3(10.0f)) ;
	//最终颜色计算
	vec3 ambient = lightd.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = diff * vec3(texture(material.diffuse, TexCoords)) * lightd.diffuse;
	vec3 specular = spec * specStrength * lightd.diffuse * 0.5f;
	vec3 final;
	final = diffuse + ambient + specular;
	
	return final;
}
vec3 CaculateLightPoint(LightPoint lightp, vec3 normal, vec3 fragPos,vec3 viewDir)
{
	vec3 lightDir = normalize(lightp.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(lightp.position - fragPos);
    float attenuation = 1.0 / (lightp.constant + lightp.linear * distance + 
                 lightp.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = lightp.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = lightp.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = lightp.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
	vec3 final = ambient + diffuse + specular;
	return final;
}
