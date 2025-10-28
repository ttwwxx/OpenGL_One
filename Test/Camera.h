#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
//#ifndef CAMERA_H
//#define	CAMERA_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>



class Camera
{
public:
	/*Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);*/
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch, Yaw;
	float senseX = 0.001f;
	float senseY = 0.001f;

	float speedZ = 0.001f;
	float speedX = 0.001f;
	float speedY = 0.001f;
	

	glm::mat4 GetViewMatrix();

	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPosition();
private:
	void UpdateCameraVectors();

};

//#endif // !CAMERA_H