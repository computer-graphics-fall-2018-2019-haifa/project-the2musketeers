#include "Light.h"



Light::Light()
{
	position = glm::vec3(0,0,0);
	intensity = glm::vec3(0,0,0);
	direction = glm::vec3(0,0,0);
	type = Point;
	state = ON;
}

Light::Light(glm::vec3 dir = glm::vec3(0, 0, 0))
{
	position = glm::vec3(0, 0, 0);
	intensity = glm::vec3(0, 0, 0);
	direction = dir;
	type = Parallel;
	state = ON;
}
Light::Light(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 i = glm::vec3(0, 0, 0))
{
	position = pos;
	intensity = i;
	direction = glm::vec3(0, 0, 0);
	type = Point;
	state = ON;
}
Light::~Light()
{
}


glm::vec3 Light::getPosition()
{
	return position;
}
glm::vec3 Light::setPosition(glm::vec3 pos)
{
	position = pos;
}

glm::vec3 Light::getIntensity()
{
	return intensity;
}
void Light::setIntensity(glm::vec3 i)
{
	intensity = i;
}

glm::vec3 Light::getDirection()
{
	return direction;
}
glm::vec3 Light::setDirection(glm::vec3 dir)
{
	direction = dir;
}

bool Light::isLightOn()
{
	if (state == ON)
		return 1;
	return 0;
}
void Light::changeLightState()
{
	if (state == ON)
		state = OFF;
	else
		state = ON;
}