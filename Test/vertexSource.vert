
#version 330 core   
layout (location = 2) in vec3 aPos;             
//layout (location = 3) in vec3 aColor;  
//layout (location = 4) in vec2 aTexCoord;  
layout (location = 5) in vec3 aNormal;


//out vec4 vertexColor;   
//out vec2 TexCoord;
out vec3 vertexPos;
out vec3 worldPos;
out vec3 Normal;

//uniform float xOffset;
//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()                                  
{
       gl_Position = projMat * viewMat * modelMat * vec4(aPos.xyz, 1.0f);
       worldPos = (modelMat * vec4(aPos.xyz, 1.0f)).xyz;
       vertexPos = aPos;
       Normal = mat3(transpose(inverse(modelMat))) * aNormal;
       //TexCoord = aTexCoord;
      // vertexColor = vec4(aColor.x , aColor.y  , aColor.z, 1.0); 
}