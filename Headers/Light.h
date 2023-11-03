#pragma once
#include <glm/glm.hpp>
#include "../Headers/Observer/Subject.h"
class Light : public Subject
{
private:
    glm::vec3 position;
    glm::vec3 color;
    float constAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float distance;
    float attenuation;
public:
    Light(glm::vec3 pos, glm::vec3 color);
    Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q,float dist);
    ~Light();
    void notify() override;
    glm::vec3 getPosition();
    glm::vec3 getColor();
    float getAttenuation();
};

