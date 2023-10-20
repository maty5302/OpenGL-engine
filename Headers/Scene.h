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
	Camera* camera;
public:	
	Scene();
	~Scene();
	Camera* getCamera();
	void makeScene();
	void makeScene2();
	void makeScene3();
	void addModel(RenderModel* model);
	void render();
};

