/**
* @file Camera.h
*
* @brief Camera used to render the scene from the perspective of the camera
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <vector>
#include "Shader/ShaderProgram.h"
#include "../Headers/Observer/Subject.h"
class ShaderProgram;
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
	int width;
	int height;

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
	int getResolutionWidth();
	int getResolutionHeight();
	//
	void getPosGlobal(glm::vec3 screenX);
	void setEye(glm::vec3 eye);
	void setTarget(glm::vec3 target);
	void setWindowSize(int width, int height);

	void notify() override;
};

