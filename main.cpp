/**
* @file main.cpp
* 
* @brief Main file of the project
* 
* @author Prudil Matìj PRU0059
* */

#include "Include/Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization();
	app->run();
}