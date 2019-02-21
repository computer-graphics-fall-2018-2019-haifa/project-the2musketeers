#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

enum LightType { Parallel,Point };
enum LightState { OFF, ON };

class Light
{
private:
	glm::vec3 position;
	glm::vec3 intensity;
	glm::vec3 direction;
	LightType type;
	LightState state;

public:
	Light();
	Light(glm::vec3 dir = glm::vec3(0,0,0));
	Light(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 i = glm::vec3(0, 0, 0));

	glm::vec3 getPosition();
	glm::vec3 setPosition(glm::vec3 pos);

	glm::vec3 getIntensity();
	void setIntensity(glm::vec3 i);

	glm::vec3 getDirection();
	glm::vec3 setDirection(glm::vec3 dir);

	bool isLightOn();
	void changeLightState();

	~Light();
};

