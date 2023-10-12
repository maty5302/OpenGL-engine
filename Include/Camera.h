#pragma once
#include <vector>
#include "Shader.h"
class Shader;
class Camera
{
private:
	std::vector<Shader*> shaders;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	float fov;

public:
	Camera();
	~Camera();
	void addShader(Shader* shader);
	void notify_Shaders();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};

