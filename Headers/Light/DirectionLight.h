#pragma once
#include <glm/vec3.hpp>
#include "Light.h"
class DirectionLight : public Light
{
private:
	glm::vec3 direction;
public:
	DirectionLight(glm::vec3 dir, glm::vec3 color);
	~DirectionLight();
	void notify() override;
};

