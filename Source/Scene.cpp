#include "../Include/Scene.h"
#include "../Include/Camera.h"
#include "../Include/FileLoader.h";
#include "../Include/Transformation/Rotation.h"
#include "../Include/Transformation/Translation.h"
#include "../Include/Transformation/Scale.h"
#include "../Models/sphere.hpp";
#include "../Models/suzi_smooth.hpp";

Scene::Scene()
{
	this->camera = new Camera();
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

void Scene::makeScene()
{
	Shader* shader = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexConstant.vert").c_str(), FileLoader::loadShader("Shaders/fragmentConstant.frag").c_str());
	Shader* shader2 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentlights.frag").c_str());
	Shader* shader3 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentPhong.frag").c_str());
	Shader* shader4 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentlights.frag").c_str());
	this->addModel(new RenderModel(sphere, 17280, shader));
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-2.5f, 0.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(sphere, 17280, shader2));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(0.0f, 2.5f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, 17280, shader3));
	this->models[2]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.5f, 0.0f, 0.0f)));
	this->models[2]->applyTransformations();
	this->addModel(new RenderModel(sphere, 17280, shader4));
	this->models[3]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(0.0f, -2.5f, 0.0f)));
	this->models[3]->applyTransformations();
	this->camera->addShader(shader);
	this->camera->addShader(shader2);
	this->camera->addShader(shader3);
	this->camera->addShader(shader4);
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
