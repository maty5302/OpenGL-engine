#pragma once
#include <glm/glm.hpp>
#include "../Headers/Observer/Subject.h"
class Light : public Subject
{
private:
    glm::vec3 position;
    glm::vec3 color;
    float attenuation;
public:
    Light(glm::vec3 pos, glm::vec3 color, float attenuation);
    ~Light();
    void notify() override;
    glm::vec3 getPosition();
    glm::vec3 getColor();
    float getAttenuation();
};

