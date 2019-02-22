#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <memory>
#include <imgui/imgui.h>

enum LightType { Parallel,Point };
enum LightState { OFF, ON };

class Light
{
private:
	glm::vec3 position;
	glm::vec4 intensity;
	glm::vec3 direction;
	LightType type;
	LightState state;

public:
	Light();
	Light(glm::vec3 vector3, glm::vec4 i, LightType type);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);

	glm::vec4 getIntensity();
	void setIntensity(glm::vec4 i);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 dir);

	bool isLightOn();
	void changeLightState();

	~Light();
};

