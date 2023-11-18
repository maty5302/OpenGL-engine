#include "../Headers/FileLoader.h"
#include <glm/vec4.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

std::string FileLoader::loadShader(const char* path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open())
    {
		std::cout << "Error opening file: " << path << std::endl;
		return "";
	}
    std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

Model* FileLoader::loadModel(const char* path)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

	const aiScene* scene = importer.ReadFile(path, importOptions);
	if (scene)
	{
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		std::vector<float> verticies;
		std::vector<GLuint> indicies;
		for (uint32_t j = 0; j < scene->mNumMeshes; j++) {
			for (uint32_t i = 0; i < scene->mMeshes[j]->mNumVertices; i++) {
				if (scene->mMeshes[j]->HasPositions())
				{
					verticies.push_back(scene->mMeshes[j]->mVertices[i].x);
					verticies.push_back(scene->mMeshes[j]->mVertices[i].y);
					verticies.push_back(scene->mMeshes[j]->mVertices[i].z);
				}
				if (scene->mMeshes[j]->HasNormals())
				{
					verticies.push_back(scene->mMeshes[j]->mNormals[i].x);
					verticies.push_back(scene->mMeshes[j]->mNormals[i].y);
					verticies.push_back(scene->mMeshes[j]->mNormals[i].z);
				}
				if (scene->mMeshes[j]->HasTextureCoords(0))
				{
					verticies.push_back(scene->mMeshes[j]->mTextureCoords[0][i].x);
					verticies.push_back(scene->mMeshes[j]->mTextureCoords[0][i].y);
				}				
			}

			for (uint32_t i = 0; i < scene->mMeshes[j]->mNumFaces; i++) {
				for (uint32_t k = 0; k < scene->mMeshes[j]->mFaces[i].mNumIndices; k++)
					indicies.push_back(scene->mMeshes[j]->mFaces[i].mIndices[k]);
			}
		}

		printf("verticies.size() = %d\n", verticies.size());
		printf("indicies.size() = %d\n", indicies.size());

 		return new Model(verticies,indicies);
	}
	else
	{
		std::cout << "Error loading model: " << path << std::endl;
		return nullptr;
	}
}
