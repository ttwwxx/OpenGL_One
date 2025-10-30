#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{ 
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(modelMat))) * aNormal;
    FragPos = vec3(modelMat * vec4(aPosition, 1.0));
    gl_Position = projMat * viewMat * vec4(FragPos, 1.0);
}