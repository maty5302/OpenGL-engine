#include "../Headers/Transformation/TransformationComposite.h"

TransformationComposite::TransformationComposite()
{

}

TransformationComposite::~TransformationComposite()
{
	for(auto transformation : this->transformations)
		delete transformation;
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
	for (auto transformation : this->transformations)
		transformation->compute();
}

glm::mat4 TransformationComposite::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	for (auto transformation : this->transformations)
		modelMatrix *= transformation->getModelMatrix();
	return modelMatrix;
}