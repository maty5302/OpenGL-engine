/**
* @file Material.h
*
* @brief 
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Texture.h"
class Material
{
private:
	glm::vec3 ambient_r;
	glm::vec3 diffuse_r;
	glm::vec3 specular_r;
	float shininess;
	glm::vec4 color;
	Texture* texture;
public:
	Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color);
	Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color, Texture* texture);
	Material(Texture* texture);
	~Material();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	glm::vec4 getColor();
	Texture* getTexture();
	bool isAllZero();
	float getShininess();
};