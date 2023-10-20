#include "../Headers/FileLoader.h"
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
