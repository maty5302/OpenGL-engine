/**
* @file TransformationComposite.h
*
* @brief Composite pattern for transformations
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <vector> 
#include "Transformation.h"
class TransformationComposite : public Transformation
{
private:
	
public:
	std::vector<Transformation*> transformations;
	TransformationComposite();
	~TransformationComposite();

	void addTransformation(Transformation* transformation);
	void removeTransformation(Transformation* transformation);
	void compute() override;
	glm::mat4 getModelMatrix() override;
};

