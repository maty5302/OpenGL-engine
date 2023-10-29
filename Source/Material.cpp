#include "../Headers/Material.h"

Material::Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color)
{
	this->ambient_r = ambient_r;
	this->diffuse_r = diffuse_r;
	this->specular_r = specular_r;
	this->shininess = shininess;
	this->color = color;
}

Material::~Material()
{
}

glm::vec3 Material::getAmbient()
{
	return this->ambient_r;
}

glm::vec3 Material::getDiffuse()
{
	return this->diffuse_r;
}

glm::vec3 Material::getSpecular()
{
	return this->specular_r;
}

float Material::getShininess()
{
	return this->shininess;
}

glm::vec4 Material::getColor()
{
	return this->color;
}


