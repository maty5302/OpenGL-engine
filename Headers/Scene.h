/**
* @file Scene.h
*
* @brief Class used for storing and rendering models to one scene
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <vector>
#include "../Headers/RenderModel.h"
#include "../Headers/Observer/Subject.h"
class Scene
{
private:
	std::vector<RenderModel*> models;
	std::vector<Light*> lights;
	std::vector<Shader*> shaders;
	Camera* camera;

	void attachObservers();
public:	
	Scene();
	~Scene();
	Camera* getCamera();
	void notifyLights();
	void makeScene();
	void makeScene2();
	void makeScene3();
	void addModel(RenderModel* model, Shader* shader);
	void render();
};

