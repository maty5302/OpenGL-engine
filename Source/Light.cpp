#include "../Headers/Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color, float attenuation)
{
	this->position = pos;
	this->color = color;
	this->attenuation = attenuation;
}

Light::~Light()
{
	for (auto observer : this->getObservers())
	{
		delete observer;
	}
}

void Light::notify()
{
	for (auto observer : this->getObservers())
	{
		observer->update(this);
	}
}

glm::vec3 Light::getPosition()
{
	return this->position;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

float Light::getAttenuation()
{
	return this->attenuation;
}
