/**
* @file Scene.h
*
* @brief Class used for storing and rendering models to one scene
*
* @author Prudil Mat�j PRU0059
* */
#pragma once
#include <vector>
#include "../Headers/RenderModel.h"
#include "../Headers/Observer/Subject.h"
#include "../Headers/Light/Light.h"
class Scene
{
private:
	std::vector<RenderModel*> models;
	std::vector<Light*> lights;
	std::vector<Shader*> shaders;
	Camera* camera;
	bool animated = false;
	float delta= 0.0f;
	void attachObservers();
public:	
	Scene();
	~Scene();
	Camera* getCamera();
	void notifyLights();
	void makeSceneTrees();
	void makeScenePhong();
	void makeSceneLights();
	void makeSceneResizeTest();
	void makeScenePlanets();	
	void addModel(RenderModel* model, Shader* shader);
	void render();
	void animate();
	bool isAnimated();
};

