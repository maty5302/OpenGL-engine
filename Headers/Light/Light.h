#pragma once
#include <glm/glm.hpp>
#include "../../Headers/Observer/Subject.h"
class Light : public Subject
{
protected:
    int isDefined;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
};

