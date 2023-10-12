#pragma once
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
class Transformation
{
public:
	virtual glm::mat4 getModelMatrix()=0;
	virtual void compute() = 0;
	virtual ~Transformation() {}
};

