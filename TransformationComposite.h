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

