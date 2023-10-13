#include "Include/Callback.h"
#include "Include/Camera.h"

void Callback::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (app)
	{
		Camera* c = app->getScene()->getCamera();
		if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			a += c->getTarget() * c->getSpeed();
			c->setEye(a);
			app->getScene()->getSubject()->notify();
		}
		if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			a -= c->getTarget() * c->getSpeed();
			c->setEye(a);
			app->getScene()->getSubject()->notify();
		}
		if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			glm::vec3 b = glm::cross(c->getTarget(), c->getUp());
			a -= b * c->getSpeed();
			c->setEye(a);
			app->getScene()->getSubject()->notify();
		}
		if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			glm::vec3 b = glm::cross(c->getTarget(), c->getUp());
			a += b * c->getSpeed();
			c->setEye(a);
			app->getScene()->getSubject()->notify();
		}
	}
	
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Callback::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Callback::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callback::cursor_callback(GLFWwindow* window, double x, double y)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		Camera* c = app->getScene()->getCamera();
		float xoffset = x - app->lastX;
		float yoffset = app->lastY - y;
		app->lastX = x;
		app->lastY = y;
		xoffset *= c->getSensitivity();
		yoffset *= c->getSensitivity();
		c->yaw += xoffset;
		c->pitch += yoffset;
		if (c->pitch > 89.0f)
			c->pitch = 89.0f;
		if (c->pitch < -89.0f)
			c->pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(c->yaw)) * cos(glm::radians(c->pitch));
		front.y = sin(glm::radians(c->pitch));
		front.z = sin(glm::radians(c->yaw)) * cos(glm::radians(c->pitch));
		c->setTarget(glm::normalize(front));
		app->getScene()->getSubject()->notify();
	}
	printf("cursor_callback [%f,%f]\n",x,y);
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
}
