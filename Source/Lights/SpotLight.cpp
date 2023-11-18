#include "../../Headers/Light/SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff)
{
	this->isDefined = 1;
	this->position = position;
	this->color = color;
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
	this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->diffuse = glm::vec3(1.f, 1.f, 1.f);
	this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic)
{
	this->isDefined = 1;
	this->position = position;
	this->color = color;
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->diffuse = glm::vec3(1.f, 1.f, 1.f);
	this->specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

SpotLight::~SpotLight()
{
	for(auto observer : this->getObservers())
		delete observer;
}

void SpotLight::notify()
{
	for (auto observer : this->getObservers())
	{
		//observer->update("spotLight.position", this->position);
		observer->update("spotLight.isDefined", this->isDefined);
		observer->update("spotLight.color", this->color);
		//observer->update("spotLight.direction", this->direction);
		observer->update("spotLight.cutOff", this->cutOff);
		observer->update("spotLight.outerCutOff", this->outerCutOff);
		observer->update("spotLight.constant", this->constant);
		observer->update("spotLight.linear", this->linear);
		observer->update("spotLight.quadratic", this->quadratic);
		observer->update("spotLight.ambient", this->ambient);
		observer->update("spotLight.diffuse", this->diffuse);
		observer->update("spotLight.specular", this->specular);
	}
}

