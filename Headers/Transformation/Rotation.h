/**
* @file Rotation.h
*
* @brief Class used for rotation of objects
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include "Transformation.h"
class Rotation : public Transformation
{
private:
	glm::mat4 modelMatrix;
	float angle;
	glm::vec3 axis;
public: 
	Rotation(float angle, glm::vec3 axis);
	~Rotation() override;
	glm::mat4 getModelMatrix() override;
	void compute() override;
};

