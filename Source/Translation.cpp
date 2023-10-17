#include "../Include/Transformation/Translation.h"

Translation::Translation(glm::vec3 translation)
{
	this->translation = translation;
	this->modelMatrix = glm::mat4(1.0f);
}

Translation::~Translation()
{
}

glm::mat4 Translation::getModelMatrix()
{
	return this->modelMatrix;
}

void Translation::compute()
{
	this->modelMatrix = glm::translate(glm::mat4(1.0f), this->translation);
}
