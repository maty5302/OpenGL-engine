#include "../Headers/Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color)
{
	this->position = pos;
	this->color = color;
	this->constAttenuation = 1.0f;
	this->linearAttenuation = 0.1f;
	this->quadraticAttenuation = 1.0f;
	this->distance = 0.5f;
	this->attenuation = 1.0f / (this->constAttenuation + this->linearAttenuation * this->distance + this->quadraticAttenuation * (this->distance * this->distance));
}

Light::Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q, float dist)
{
	this->position = pos;
	this->color = color;
	this->constAttenuation = c;
	this->linearAttenuation = l;
	this->quadraticAttenuation = q;
	this->distance = dist;
	this->attenuation = 1.0f / (this->constAttenuation + this->linearAttenuation * this->distance + this->quadraticAttenuation * (this->distance * this->distance));
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
	return glm::max(this->attenuation, 0.0f);
}
