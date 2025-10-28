#include "Camera.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
//#ifndef CAMERA_H
//#define	CAMERA_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//Camera:: Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
//{
//	Position = position;
//	Forward = glm::normalize(position - target);
//	WorldUp = worldup;
//	Right = glm::normalize(glm::cross(worldup,position));
//	Up = glm::normalize(glm::cross(position, Right));
//}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Yaw = yaw;
	Pitch = pitch;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);		   
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
	
}
glm::mat4 Camera::GetViewMatrix()
{
	float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = sin(glfwGetTime()) * radius;
	return glm::lookAt(Position, Position - Forward, WorldUp);
}
void Camera::UpdateCameraVectors()
{
	//¸üÐÂpitchºÍyaw
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);		   
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera:: ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * senseY;
	Yaw -= deltaX * senseX;
	UpdateCameraVectors();
}
void Camera::UpdateCameraPosition()
{
	Position += Forward * speedZ * 0.1f + Right * speedX * 0.1f + Up * speedY * 0.1f;
}