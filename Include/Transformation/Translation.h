#pragma once
#include "Transformation.h"
class Translation : public Transformation
{
private:
	glm::mat4 modelMatrix;
	glm::vec3 translation;
public:
	Translation(glm::vec3 translation);
	~Translation() override;
	glm::mat4 getModelMatrix() override;
	void compute() override;
};

