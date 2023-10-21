#pragma once
#include <glm/glm.hpp>
#include "../Headers/Observer/Subject.h"
class Light : public Subject
{
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
public:
    Light(glm::vec3 pos, glm::vec3 color, float intensity);
    ~Light();
    void notify() override;
    glm::vec3 getPosition();
    glm::vec3 getColor();
    float getIntensity();
};

