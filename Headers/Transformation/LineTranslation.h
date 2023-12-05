#pragma once
#include <glm/ext/vector_float3.hpp>
#include "Transformation.h"
class LineTranslation : public Transformation
{
private:
	glm::mat4 modelMatrix;
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 current;
	float t;
	float delta;
	bool moveback = false;
public:
	LineTranslation(glm::vec3 start, glm::vec3 end, float &t);
	~LineTranslation();
	glm::vec3 getCurrent();
	glm::mat4 getModelMatrix();
	void compute();
};

