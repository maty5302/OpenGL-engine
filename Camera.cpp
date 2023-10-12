#include "Include/Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
{
    this->eye = glm::vec3(0.0f, 0.0f, 3.0f);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = 90.f;
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(this->fov), 4.0f / 3.0f,  0.1f, 100.0f);
}

void Camera::addShader(Shader* shader)
{
	this->shaders.push_back(shader);
}