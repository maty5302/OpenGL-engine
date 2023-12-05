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
	std::vector<Model*> preloadModels;
	std::vector<RenderModel*> models;
	std::vector<Light*> lights;
	std::vector<ShaderProgram*> shaderPrograms;
	RenderModel* skybox;
	Camera* camera;
	bool animated = false;
	float delta= 0.01f;

	//private methods
	void attachObservers();
	void animatePlanets();
public:	
	Scene();
	Scene(Model* skybox, Texture* texture);
	~Scene();
	//getters
	Camera* getCamera();
	Model* getPreloadModel(int id);
	//adding/removing
	void addModel(RenderModel* model);
	void addModel(RenderModel* model, glm::vec3 location);
	void removeModel(int id);
	//voids
	void notifyLights();
	//scene making
	void makeScene();
	void makeScenePhong();
	void makeSceneTest();
	void makeScenePlanets();
	//rendering
	void render();
	void renderSkybox();
};

