/**
* @file Application.h
*
* @brief Handles the application, window and scenes
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Headers/Scene.h"
#include "../Headers/Callback.h"
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

