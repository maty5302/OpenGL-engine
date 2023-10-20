#include "../Headers/Scene.h"
#include "../Headers/Camera.h"
#include "../Headers/FileLoader.h";
#include "../Headers/Transformation/Rotation.h"
#include "../Headers/Transformation/Translation.h"
#include "../Headers/Transformation/Scale.h"
#include "../Models/sphere.hpp";
#include "../Models/suzi_smooth.hpp";
#include "../Models/suzi_flat.hpp";

Scene::Scene()
{
	this->camera = new Camera(); //make camera in application
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
	//Scene 4 spheres and light in the middle of them
	Shader* shader = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexConstant.vert").c_str(), FileLoader::loadShader("Shaders/fragmentConstant.frag").c_str());
	Shader* shader2 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentLambert.frag").c_str());
	Shader* shader3 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentPhong.frag").c_str());
	Shader* shader4 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentBlinn.frag").c_str());
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

void Scene::makeScene2()
{
	//Scene one object between light and camera //needs to be fixed and add light
	Shader* shader2 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentPhong.frag").c_str());
	this->addModel(new RenderModel(sphere, 17280, shader2));
	this->models[0]->addTransformation(new Scale(glm::vec3(0.2f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(0.0f, -2.0f, 2.0f)));
	this->models[0]->applyTransformations();
	this->camera->addShader(shader2);
}

void Scene::makeScene3()
{
	//Scene objects with different shaders, constant, lambert and phong //todo add light and blinn-phong shader
	Shader* shader = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexConstant.vert").c_str(), FileLoader::loadShader("Shaders/fragmentConstant.frag").c_str());
	Shader* shader2 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentLambert.frag").c_str());
	Shader* shader3 = new Shader(this->camera, FileLoader::loadShader("Shaders/vertexlights.vert").c_str(), FileLoader::loadShader("Shaders/fragmentPhong.frag").c_str());

	this->addModel(new RenderModel(sphere, 17280, shader));
	this->addModel(new RenderModel(suziFlat, 17424, shader2));
	this->addModel(new RenderModel(suziSmooth, 17424, shader3));

	for(RenderModel* model : this->models)
		model->addTransformation(new Scale(glm::vec3(0.7f)));

	this->models[0]->addTransformation(new Translation(glm::vec3(-2.5f, 2.5f, 0.0f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(2.5f, 2.5f, 0.0f)));
	this->models[2]->addTransformation(new Translation(glm::vec3( - 2.5f, -2.5f, 0.0f)));

	for(RenderModel* model : this->models)
		model->applyTransformations();

	this->camera->addShader(shader);
	this->camera->addShader(shader2);
	this->camera->addShader(shader3);
}

//this is now bullshit
void Scene::addModel(RenderModel* model)
{
	this->models.push_back(model);
}

void Scene::render()
{
	for (auto model : models)
		model->render();
}
