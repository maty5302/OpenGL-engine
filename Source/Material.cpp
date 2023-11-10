	#include "../Headers/Material.h"

Material::Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color)
{
	this->ambient_r = ambient_r;
	this->diffuse_r = diffuse_r;
	this->specular_r = specular_r;
	this->shininess = shininess;
	this->color = color;
	this->texture = nullptr;
}

Material::Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color, Texture* texture)
{
	this->ambient_r = ambient_r;
	this->diffuse_r = diffuse_r;
	this->specular_r = specular_r;
	this->shininess = shininess;
	this->color = color;
	this->texture = texture;
}

Material::Material(Texture* texture)
{
	this->texture = texture;
	this->ambient_r = glm::vec3(0.0f);
	this->diffuse_r = glm::vec3(0.0f);
	this->specular_r = glm::vec3(0.0f);
	this->shininess = 0.0f;
	this->color = glm::vec4(0.0f);
}

Material::~Material()
{
	delete this->texture;
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

bool Material::isAllZero()
{
	if(this->ambient_r == glm::vec3(0.0f) && this->diffuse_r == glm::vec3(0.0f) && this->specular_r == glm::vec3(0.0f) && this->shininess == 0.0f && this->color == glm::vec4(0.0f))
		return true;
	else
		return false;
}

float Material::getShininess()
{
	return this->shininess;
}

glm::vec4 Material::getColor()
{
	return this->color;
}

Texture* Material::getTexture()
{
	return this->texture;
}


