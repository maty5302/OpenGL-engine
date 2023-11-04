#pragma once
#include "Light.h"
class SpotLight : public Light
{
private:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
public:
    SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff);
    SpotLight(glm::vec3 position,glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic);
	~SpotLight();
    void notify() override;
};

