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
#include <vector>
#include "../Headers/Scene.h"
#include "../Headers/Callback.h"
class Application
{
private:
	std::vector<Scene*> scenes;
	GLFWwindow* window;	
	Scene* activeScene;
public:
	float lastX = 400, lastY = 300;
	int width = 800, height = 600;
	Scene* getScene();
	void setScene(int sceneNumber);
	void initialization();
	void run();
	Application();
	~Application();      
};

