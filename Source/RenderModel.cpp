#include "../Headers/RenderModel.h"
#include "../Headers/Transformation/TransformationComposite.h"

RenderModel::RenderModel(const float points[], int pointsCount,Shader* shader)
{
	glm::mat4 defaulfM = glm::mat4(1.0f);
	this->model = new Model(points, pointsCount);
	this->shader = shader;
	this->transform = new TransformationComposite();
	this->shader->useShader();
	this->shader->setMatrixModel(defaulfM);
}

void RenderModel::applyTransformations()
{
	this->transform->compute();
	this->shader->setMatrixModel(this->transform->getModelMatrix());
}

void RenderModel::addTransformation(Transformation* transformation)
{
	this->transform->addTransformation(transformation);
}

void RenderModel::removeTransformation(Transformation* transformation)
{
	this->transform->removeTransformation(transformation);
}

void RenderModel::render()
{
	this->shader->useShader();
	this->model->useModel();	
}

RenderModel::~RenderModel()
{
	delete model;
	delete shader;
	delete transform;
}
