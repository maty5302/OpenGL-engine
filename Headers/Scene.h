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
#include "../Headers/Light/Light.h"
class Scene
{
private:
	std::vector<RenderModel*> models;
	std::vector<Light*> lights;
	std::vector<ShaderProgram*> shaderPrograms;
	RenderModel* skybox;
	Camera* camera;
	bool animated = false;
	float delta= 0.0f;
	void attachObservers();
public:	
	Scene();
	Scene(Model* skybox, Texture* texture);
	~Scene();
	Camera* getCamera();
	void notifyLights();
	void makeScene();
	void makeSceneTrees();
	void makeScenePhong();
	void makeSceneTest();
	void makeSceneResizeTest();
	void makeScenePlanets();	
	void addModel(RenderModel* model);
	void render();
	void renderSkybox();
	void animate();
	bool isAnimated();
};

