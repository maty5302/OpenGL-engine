#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Texture
{
private:
	GLuint textureID = 0;
	int textureUnitID = 0;
public:
	Texture(const char* filePath, int textureUnitID);
	int getTextureUnitID();
};

