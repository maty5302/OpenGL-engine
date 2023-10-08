#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "RenderModel.h"
#include "Callback.h"
class Application
{
private:
	GLFWwindow* window;
	std::vector<RenderModel*> renderModels;
	
public:
	void initialization();
	void createShaderAndModels();
	void run();
	Application();
	~Application();      
};

