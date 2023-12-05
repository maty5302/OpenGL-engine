#pragma once
#include "Transformation.h"
#include <vector>
class BezierTranslation : public Transformation
{
private:
	glm::mat4 bezierMatrix;
	glm::mat4x3 currentPoints;
	std::vector<glm::vec3> points;
	float t;
	float delta;
	glm::mat4 modelMatrix;
	bool moveback = false;
	int counter = 0;

public:
	BezierTranslation(float t);	
	~BezierTranslation() override;
	void addPoint(glm::vec3 point);
	void compute() override;
	glm::mat4 getModelMatrix() override;
};

