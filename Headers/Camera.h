/**
* @file Camera.h
*
* @brief Camera used to render the scene from the perspective of the camera
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <vector>
#include "Shader.h"
#include "../Headers/Observer/Subject.h"
class Shader;
class Camera : public Subject 
{
private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 projectionMatrix;
	float fov;
	float sensitivity;
	float speed;

public:
	float yaw;
	float pitch;

	Camera();
	~Camera();
	//getters and setters
	glm::vec3 getEye();
	glm::vec3 getTarget();
	glm::vec3 getUp();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	float getSensitivity();
	float getSpeed();
	void setEye(glm::vec3 eye);
	void setTarget(glm::vec3 target);

	void addShader(Shader* shader);
	void notify() override;
};

