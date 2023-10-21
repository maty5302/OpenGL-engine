#include "../Headers/Scene.h"
#include "../Headers/Camera.h"
#include "../Headers/FileLoader.h";
#include "../Headers/Transformation/Rotation.h"
#include "../Headers/Transformation/Translation.h"
#include "../Headers/Transformation/Scale.h"
#include "../Headers/Light.h"
#include "../Models/sphere.hpp";
#include "../Models/suzi_smooth.hpp";
#include "../Models/suzi_flat.hpp";
#include "../Models/tree.hpp";

void Scene::attachObservers()
{
	for (auto light : this->lights)
		for (auto observer : this->shaders)
			light->addObserver(observer);
	this->notifyLights();
}

Scene::Scene()
{
	this->camera = new Camera();
	this->lights = std::vector<Light*>();
	this->models = std::vector<RenderModel*>();
}

Scene::~Scene()
{
	delete this->camera;

	for (auto model : this->models)
		delete model;
	for(auto light : this->lights)
		delete light;
	for(auto shader : this->shaders)
		delete shader;
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::notifyLights()
{
	for (auto light : this->lights)
		light->notify();
}

void Scene::makeScene()
{
	//Scene 4 spheres and light in the middle of them
	this->lights.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.5f));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[0]), this->shaders[0]);
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-2.5f, 0.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[1]), this->shaders[1]);
	this->models[1]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(0.0f, 2.5f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[2]), this->shaders[2]);
	this->models[2]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.5f, 0.0f, 0.0f)));
	this->models[2]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[3]), this->shaders[3]);
	this->models[3]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(0.0f, -2.5f, 0.0f)));
	this->models[3]->applyTransformations();
	this->attachObservers();
}


void Scene::makeScene2()
{
	//Scene one object between light and camera //needs to be fixed and add light
	this->lights.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.5f));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[0]), this->shaders[0]);
	this->models[0]->addTransformation(new Scale(glm::vec3(0.2f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(0.0f, -2.0f, 2.0f)));
	this->models[0]->applyTransformations();
	this->attachObservers();	
}

void Scene::makeScene3()
{
	//Scene objects with different shaders, constant, lambert and phong //todo add light and blinn-phong shader
	this->lights.push_back(new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.5f));

	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexConstant.vert").c_str(), FileLoader::loadShader("Shaders/fragmentConstant.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentLambert.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentPhong.frag").c_str()));
	this->shaders.push_back(new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str()));

	this->addModel(new RenderModel(tree, sizeof(tree) / sizeof(float), this->shaders[0]), this->shaders[0]);
	this->addModel(new RenderModel(suziFlat, sizeof(suziFlat) / sizeof(float), this->shaders[1]), this->shaders[1]);
	this->addModel(new RenderModel(suziSmooth, sizeof(suziSmooth) / sizeof(float), this->shaders[2]), this->shaders[2]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[3]), this->shaders[3]);

	for(RenderModel* model : this->models)
		model->addTransformation(new Scale(glm::vec3(0.7f)));


	this->models[0]->addTransformation(new Translation(glm::vec3(-2.5f, 2.5f, 0.0f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(2.5f, 2.5f, 0.0f)));
	this->models[2]->addTransformation(new Translation(glm::vec3( - 2.5f, -2.5f, 0.0f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(2.5f, -2.5f, 0.0f)));


	this->models[0]->addTransformation(new Scale(glm::vec3(0.3f)));

	for(RenderModel* model : this->models)
		model->applyTransformations();

	this->attachObservers();
}

void Scene::addModel(RenderModel* model, Shader* shader)
{
	this->models.push_back(model);
	this->camera->addObserver(shader);
}

void Scene::render()
{
	for (auto model : this->models)
		model->render();
}
