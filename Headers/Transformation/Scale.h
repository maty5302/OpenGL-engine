/**
* @file Scale.h
*
* @brief Class for scaling objects
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include "Transformation.h"
class Scale : public Transformation
{
private:
	glm::mat4 modelMatrix;
	glm::vec3 scale;
public:
	Scale(glm::vec3 scale);
	~Scale() override;
	glm::mat4 getModelMatrix() override;
	void compute() override;
};

