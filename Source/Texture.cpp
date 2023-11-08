#include "../Headers/Texture.h"
#include <SOIL2/SOIL2.h>

Texture::Texture(const char* filePath, int textureUnitID)
{
	this->textureUnitID = textureUnitID;
	glActiveTexture(GL_TEXTURE0 + textureUnitID);
	this->textureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

int Texture::getTextureUnitID()
{
	return this->textureUnitID;
}
