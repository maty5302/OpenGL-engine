#include "../Include/Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
{
    this->eye = glm::vec3(0.0f, 0.0f, 3.0f);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = 90.f;
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), 4.0f / 3.0f, 0.1f, 100.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->sensitivity = 0.05f;
    this->speed = 0.05f;
}

Camera::~Camera()
{
    for (Shader* shader : this->shaders)
    {
		delete shader;
	}
}

glm::vec3 Camera::getEye()
{
    return this->eye;
}

glm::vec3 Camera::getTarget()
{
    return this->target;
}

glm::vec3 Camera::getUp()
{
    return this->up;
}

float Camera::getSensitivity()
{
    return this->sensitivity;
}

float Camera::getSpeed()
{
    return this->speed;
}

void Camera::setEye(glm::vec3 eye)
{
    this->eye = eye;
}

void Camera::setTarget(glm::vec3 target)
{
    this->target = target;
}

void Camera::update()
{
    for (Shader* shader : this->shaders)
    {
        shader->update();
    }
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::addShader(Shader* shader)
{   
	this->shaders.push_back(shader);
}