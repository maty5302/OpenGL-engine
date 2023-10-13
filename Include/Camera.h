#pragma once
#include <vector>
#include "Shader.h"
#include "Include/Observer/Observer.h"
class Shader;
class Camera : public Observer
{
private:
	std::vector<Shader*> shaders;
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
	void update() override;
};

