#include "../../Headers/Light/DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 dir, glm::vec3 color)
{
	this->isDefined = 1;
	this->direction = dir;
	this->color = color;
	this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

DirectionLight::~DirectionLight()
{
	for(auto observer : this->getObservers())
	{
		delete observer;
	}
}

void DirectionLight::notify()
{
	for (auto observer : this->getObservers())
	{
		observer->update("dirLight.isDefined", this->isDefined);
		observer->update("dirLight.direction", this->direction);
		observer->update("dirLight.color", this->color);
		observer->update("dirLight.ambient", this->ambient);
		observer->update("dirLight.diffuse", this->diffuse);
		observer->update("dirLight.specular", this->specular);
	}
}
