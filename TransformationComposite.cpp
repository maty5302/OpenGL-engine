#include "TransformationComposite.h"

TransformationComposite::TransformationComposite()
{

}

TransformationComposite::~TransformationComposite()
{
}

void TransformationComposite::addTransformation(Transformation* transformation)
{
	this->transformations.push_back(transformation);
}

void TransformationComposite::removeTransformation(Transformation* transformation)
{
	this->transformations.erase(std::remove(this->transformations.begin(), this->transformations.end(), transformation), this->transformations.end());
}

void TransformationComposite::compute()
{
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		this->transformations[i]->compute();
	}
}

glm::mat4 TransformationComposite::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		modelMatrix *= this->transformations[i]->getModelMatrix();
	}
	return modelMatrix;
}