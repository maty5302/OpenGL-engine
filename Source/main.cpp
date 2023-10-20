/**
* @file main.cpp
* 
* @brief Main file of the project
* 
* @author Prudil Mat�j PRU0059
* */

#include "../Headers/Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization();
	app->run();
}