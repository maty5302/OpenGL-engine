#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Include/Scene.h"
#include "Include/Callback.h"
class Application
{
private:
	GLFWwindow* window;	
	Scene* scene;
public:
	float lastX = 400, lastY = 300;
	Scene* getScene();
	void initialization();
	void run();
	Application();
	~Application();      
};

