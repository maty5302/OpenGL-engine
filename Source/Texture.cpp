#include "../Headers/Texture.h"
#include <SOIL2/SOIL2.h>

Texture::Texture(const char* filePath, int textureUnitID)
{
	this->textureUnitID = textureUnitID;
	glActiveTexture(GL_TEXTURE0 + textureUnitID);
	this->textureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::Texture(const char* filePosx, const char* fileNegx, const char* filePosy, const char* fileNegy, const char* filePosz, const char* fileNegz, int textureUnitID)
{
	this->textureUnitID = textureUnitID;
	glActiveTexture(GL_TEXTURE0 + textureUnitID);
	this->textureID = SOIL_load_OGL_cubemap(filePosx, fileNegx, filePosy, fileNegy, filePosz, fileNegz, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

int Texture::getTextureUnitID()
{
	return this->textureUnitID;
}
