#include "../../Headers/Light/PointLight.h"
#include <string>

PointLight::PointLight(glm::vec3 pos, glm::vec3 color)
{
	this->isDefined = 1;
	this->position = pos;
	this->color = color;
	this->constAttenuation = 1.0f;
	this->linearAttenuation = 0.09f;
	this->quadraticAttenuation = 0.032f;
	this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float c, float l, float q)
{
	this->isDefined = 1;
	this->position = pos;
	this->color = color;
	this->constAttenuation = c;
	this->linearAttenuation = l;
	this->quadraticAttenuation = q;
	this->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	this->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

PointLight::~PointLight()
{
	for (auto observer : this->getObservers())
	{
		delete observer;
	}
}

void PointLight::notify(int id)
{
	for (auto observer : this->getObservers())
	{
		std::string name = "pointLight["+std::to_string(id)+"].";
		observer->update((name+"position").c_str(), this->position);
		observer->update((name + "isDefined").c_str(), this->isDefined);
		observer->update((name+"color").c_str(), this->color);
		observer->update((name+"constant").c_str(), this->constAttenuation);
		observer->update((name+"linear").c_str(), this->linearAttenuation);
		observer->update((name+"quadratic").c_str(), this->quadraticAttenuation);
		observer->update((name+"ambient").c_str(), this->ambient);
		observer->update((name+"diffuse").c_str(), this->diffuse);
		observer->update((name+"specular").c_str(), this->specular);

		/*observer->update("testovacisubjekt.position", this->position);
		observer->update("testovacisubjekt.color",this->color);
		observer->update("testovacisubjekt.constant", this->constAttenuation);
		observer->update("testovacisubjekt.linear", this->linearAttenuation);
		observer->update("testovacisubjekt.quadratic", this->quadraticAttenuation);
		observer->update("testovacisubjekt.ambient", this->ambient);
		observer->update("testovacisubjekt.diffuse", this->diffuse);
		observer->update("testovacisubjekt.specular", this->specular);*/
	}
}