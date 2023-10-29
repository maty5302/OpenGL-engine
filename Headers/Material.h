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
class Material
{
private:
	glm::vec3 ambient_r;
	glm::vec3 diffuse_r;
	glm::vec3 specular_r;
	float shininess;
	glm::vec4 color;
public:
	Material(glm::vec3 ambient_r, glm::vec3 diffuse_r, glm::vec3 specular_r, float shininess, glm::vec4 color);
	~Material();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
	glm::vec4 getColor();
};