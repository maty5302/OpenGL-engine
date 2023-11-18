/**
* @file FileLoader.h
*
* @brief Class used for loading files
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include <string>
#include "../Headers/Model.h"
static class FileLoader
{
public:
	static std::string loadShader(const char* path);
    static Model* loadModel(const char* path);
};