#include "../Headers/RenderModel.h"
#include "../Headers/Transformation/TransformationComposite.h"

RenderModel::RenderModel(Model* model, Shader* shader, Material* material)
{
	glm::mat4 defaulfM = glm::mat4(1.0f);
	this->model = model;
	this->shader = shader;
	this->transform = new TransformationComposite();
	this->shader->useShader();
	this->shader->setMatrixModel(defaulfM);
	this->material = material;
	this->shader->setUniform("objectColor", this->material->getColor());
	this->shader->setUniform("shininess", this->material->getShininess());
	this->shader->setUniform("specularStrength", this->material->getSpecular());
	this->shader->setUniform("ambientStrength", this->material->getAmbient());

}

RenderModel::RenderModel(const float points[], int pointsCount, Shader* shader, Material* material)
{
	glm::mat4 defaulfM = glm::mat4(1.0f);
	this->model = new Model(points, pointsCount);
	this->shader = shader;
	this->transform = new TransformationComposite();
	this->shader->useShader();
	this->shader->setMatrixModel(defaulfM);
	this->material = material;
	this->shader->setUniform("objectColor", this->material->getColor());
	this->shader->setUniform("shininess", this->material->getShininess());
	this->shader->setUniform("specularStrength", this->material->getSpecular());
	this->shader->setUniform("ambientStrength", this->material->getAmbient());
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
	delete material;
}
