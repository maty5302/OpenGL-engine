#pragma once
#include <glm/glm.hpp>
#include "Light.h"
class PointLight : public Light
{
private:
    glm::vec3 position;
    float constAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
public:
    PointLight(glm::vec3 pos, glm::vec3 color);
    PointLight(glm::vec3 pos, glm::vec3 color, float c, float l, float q);
    ~PointLight();
    void notify(int id) override;

};

