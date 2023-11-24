#include "../Headers/RenderModel.h"
#include "../Headers/Transformation/TransformationComposite.h"

int RenderModel::ID = 0;

RenderModel::RenderModel(Model* model, ShaderProgram* shader, Material* material,bool setID)
{
	glm::mat4 defaulfM = glm::mat4(1.0f);
	if(setID)
		this->objID = ID++;
	this->model = model;
	this->shaderProgram = shader;
	this->transform = new TransformationComposite();
	this->shaderProgram->useShader();
	this->shaderProgram->setMatrixModel(defaulfM);
	this->material = material;
	if (!this->material->isAllZero()) {
		this->shaderProgram->setUniform("objectColor", this->material->getColor());
		this->shaderProgram->setUniform("shininess", this->material->getShininess());
		this->shaderProgram->setUniform("specularStrength", this->material->getSpecular());
		this->shaderProgram->setUniform("ambientStrength", this->material->getAmbient());
	}
	if (this->material->getTexture() != nullptr)
		this->shaderProgram->setUniform("textureUnitID", this->material->getTexture()->getTextureUnitID());
}

RenderModel::RenderModel(const float points[], int pointsCount, ShaderProgram* shader, Material* material, bool texture, bool normal)
{
	glm::mat4 defaulfM = glm::mat4(1.0f);
	this->objID = ID++;
	this->model = new Model(points, pointsCount, texture,normal);
	this->shaderProgram = shader;
	this->transform = new TransformationComposite();
	this->shaderProgram->useShader();
	this->shaderProgram->setMatrixModel(defaulfM);
	this->material = material;
	if (!this->material->isAllZero()) {
		this->shaderProgram->setUniform("objectColor", this->material->getColor());
		this->shaderProgram->setUniform("shininess", this->material->getShininess());
		this->shaderProgram->setUniform("specularStrength", this->material->getSpecular());
		this->shaderProgram->setUniform("ambientStrength", this->material->getAmbient());
	}
	if (this->material->getTexture() != nullptr)
		this->shaderProgram->setUniform("textureUnitID", this->material->getTexture()->getTextureUnitID());
}


void RenderModel::applyTransformations()
{
	this->transform->compute();
	this->shaderProgram->setMatrixModel(this->transform->getModelMatrix());
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
	this->shaderProgram->useShader();
	this->model->useModel();	
}

int RenderModel::getID()
{
	return this->objID;
}

ShaderProgram* RenderModel::getShaderProgram()
{
	return this->shaderProgram;
}

RenderModel::~RenderModel()
{
	delete model;
	delete shaderProgram;
	delete transform;
	delete material;
}
