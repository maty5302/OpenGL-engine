#include "../Headers/Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>

Camera::Camera()
{
    this->eye = glm::vec3(0.0f, 0.0f, 3.0f);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = 70.f;
    this->width = 800;
    this->height = 600;
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), (float)this->width / (float)this->height, 0.1f, 100.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->sensitivity = 0.05f;
    this->speed = 0.1f;
}

Camera::~Camera()
{
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
    this->notify(); 
}

void Camera::setTarget(glm::vec3 target)
{
    this->target = target;
    this->notify();
}

void Camera::setWindowSize(int width, int height)
{
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), (float)width / (float)height, 0.1f, 100.0f);
    this->notify();
}

int Camera::getResolutionWidth()
{
    return this->width;
}

int Camera::getResolutionHeight()
{
    return this->height;
}

void Camera::getPosGlobal(glm::vec3 screenX)
{
    glm::vec4 viewPort = glm::vec4(0, 0, this->width, this->height);
    glm::vec3 pos = glm::unProject(screenX, this->getViewMatrix(), this->getProjectionMatrix(), viewPort);

    printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::notify()
{
    for (auto observer : this->getObservers())
    {
        observer->update("viewMatrix", this->getViewMatrix());
        observer->update("projectionMatrix", this->getProjectionMatrix());
        observer->update("cameraPosition", this->getEye());
        observer->update("spotLight.position", this->getEye());
        observer->update("spotLight.direction", this->getTarget());
	}
}
