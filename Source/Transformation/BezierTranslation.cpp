#include "../../Headers/Transformation/BezierTranslation.h"

BezierTranslation::BezierTranslation(float t)
{
	this->bezierMatrix = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
									glm::vec4(3.0, -6.0, 3.0, 0),
									glm::vec4(-3.0, 3.0, 0, 0),
									glm::vec4(1, 0, 0, 0));
	this->currentPoints = glm::mat4x3(1.0f);
	this->t = t;
	this->delta = 0.01f;
	this->modelMatrix = glm::mat4(1.0f);
}

BezierTranslation::~BezierTranslation()
{
}

void BezierTranslation::addPoint(glm::vec3 point)
{
	points.push_back(point);
}

void BezierTranslation::compute()
{
	int max = (points.size() / 4)-1;

	if (points.size() < 4)
			return;

	currentPoints = glm::mat4x3(points[counter*4], points[counter*4+1], points[counter*4+2], points[counter*4+3]);
	
	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

	glm::vec3 p = parameters * bezierMatrix * glm::transpose(currentPoints);

	this->modelMatrix = glm::translate(glm::mat4(1.0f),p);

	if (t >= 1.0f || t <= 0.0f)
	{
		if (counter < max && !moveback)
		{
			counter++;
			t = 0.0f;
		}
		else if (counter == max && !moveback)
		{
			moveback = true;
			delta *= -1;
		}
		else if (counter > 0 && moveback)
		{
			counter--;
			t = 1.0f;
		}
		else if (counter == 0 && moveback)
		{
			moveback = false;
			delta *= -1;
		}
	}
	t += delta;
}

glm::mat4 BezierTranslation::getModelMatrix()
{
	return this->modelMatrix;
}