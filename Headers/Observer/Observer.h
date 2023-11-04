#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
class Subject;
class Observer {
public:
	virtual void update(const char* name, glm::vec4 value) = 0;
	virtual void update(const char* name, glm::vec3 value) = 0;
	virtual void update(const char* name, float value) = 0;
	virtual void update(const char* name, glm::mat4 value) = 0;
	virtual void update(const char* name, int value) = 0;
	virtual ~Observer() = default;
};
