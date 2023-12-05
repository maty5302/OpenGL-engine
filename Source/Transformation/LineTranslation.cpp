#include "../../Headers/Transformation/LineTranslation.h"

LineTranslation::LineTranslation(glm::vec3 start, glm::vec3 end, float &t)
{
	this->start = start;
	this->end = end;
	this->current = start;
	this->delta = 0.01f;
	this->t = t;
}

LineTranslation::~LineTranslation()
{
}

glm::vec3 LineTranslation::getCurrent()
{
	return this->current;
}

glm::mat4 LineTranslation::getModelMatrix()
{
	return this->modelMatrix;
}

void LineTranslation::compute()
{
	if (t < 1.0f && !moveback)
	{
		t += delta;
		current = start + t * (end - start);
	}
	else if (t >= 1.0f && !moveback)
	{
		t = 1.0f;
		current = end;
		moveback = true;
	}
	else if (t > 0.0f && moveback)
	{
		t -= delta;
		current = start + t * (end - start);
	}
	else if (t <= 0.0f && moveback)
	{
		t = 0.0f;
		current = start;
		moveback = false;
	}
	else
	{
		t = 0.0f;
		current = start;
	}

	this->modelMatrix = glm::translate(glm::mat4(1.0f), this->getCurrent());
}
