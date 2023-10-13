#include "Include/Scene.h"
#include "Include/Camera.h"
#include "Include/Transformation/Rotation.h"
#include "Include/Transformation/Translation.h"
#include "Include/Transformation/Scale.h"
#include "Models/sphere.h";
#include "Models/suzi_smooth.h";

Scene::Scene()
{
	this->makeScene();
}

Scene::~Scene()
{
	delete this->camera;
}

Camera* Scene::getCamera()
{
	return this->camera;
}

Subject* Scene::getSubject()
{
	return this->subject;
}

void Scene::makeScene()
{
	this->camera = new Camera();
	Shader* shader = new Shader(this->camera);
	Shader* shader2 = new Shader(this->camera);
	Shader* shader3 = new Shader(this->camera);
	this->addModel(new RenderModel(sphere, 17280, shader));
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-0.5f, -0.2f, 0.0f)));
	this->models[0]->addTransformation(new Rotation(2.f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(suziSmooth, 17424, shader2));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.4f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(1.0f, 1.4f, 1.0f)));
	this->models[1]->addTransformation(new Rotation(2.f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, 17280, shader3));
	this->models[2]->addTransformation(new Scale(glm::vec3(0.4f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.f, 2.5f, 0.0f)));
	this->models[2]->applyTransformations();
	this->camera->addShader(shader);
	this->camera->addShader(shader2);
	this->camera->addShader(shader3);
	this->subject = new Subject();
	subject->addObserver(this->camera);
	subject->addObserver(shader);
	subject->addObserver(shader2);
	subject->addObserver(shader3);
}


void Scene::addModel(RenderModel* model)
{
	this->models.push_back(model);
}

void Scene::render()
{
	for (auto model : models)
		model->render();
}
