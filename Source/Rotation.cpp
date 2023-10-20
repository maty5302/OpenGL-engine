#include "../Headers/Transformation/Rotation.h"

Rotation::Rotation(float angle, glm::vec3 axis)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->angle = angle;
	this->axis = axis;
}

Rotation::~Rotation()
{
}

glm::mat4 Rotation::getModelMatrix()
{
	return this->modelMatrix;
}

void Rotation::compute()
{
	this->modelMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
}