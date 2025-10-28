
#version 330 core   
layout (location = 2) in vec3 aPos;             
//layout (location = 3) in vec3 aColor;  
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTexCoords;  //uv


//out vec4 vertexColor;   
out vec2 TexCoords;
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
       TexCoords = aTexCoords;
      // vertexColor = vec4(aColor.x , aColor.y  , aColor.z, 1.0); 
}