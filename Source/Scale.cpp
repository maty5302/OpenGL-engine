#include "../Headers/Transformation/Scale.h"

Scale::Scale(glm::vec3 scale)
{
	this->scale = scale;
	this->modelMatrix = glm::mat4(1.0f);
}

Scale::~Scale()
{
}

glm::mat4 Scale::getModelMatrix()
{
	return this->modelMatrix;
}

void Scale::compute()
{
	this->modelMatrix = glm::scale(glm::mat4(1.0f), this->scale);
}
