/**
* @file main.cpp
* 
* @brief Main file of the project
* 
* @author Prudil Mat�j PRU0059
* */

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
//Include my headers
#include "Application.h"

//GLM test
//
//// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
//
//// Camera matrix
//glm::mat4 View = glm::lookAt(
//	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
//	glm::vec3(0, 0, 0), // and looks at the origin
//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
//	);
//// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 Model = glm::mat4(1.0f);
//

int main(void)
{
	Application* app = new Application();
	app->initialization();

	app->createShaderAndModels();

	app->run();
}