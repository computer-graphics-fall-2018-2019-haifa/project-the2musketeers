#include "Light.h"



Light::Light()
{
	position = glm::vec3(0,0,0);
	intensity = glm::vec4(0,0,0,0);
	direction = glm::vec3(0,0,0);
	isPoint = 1;
	isON = 1;
}

Light::Light(glm::vec3 vector3, glm::vec4 i, bool pointOrParallel)
{
	if (pointOrParallel == true)
	{
		position = vector3;
	}
	else
	{
		direction = vector3;
	}

	intensity = i;
	isPoint = pointOrParallel;
	isON = true;
}
Light::~Light()
{
}


glm::vec3 Light::getPosition()
{
	return position;
}
void  Light::setPosition(glm::vec3 pos)
{
	position = pos;
}

glm::vec4 Light::getIntensity()
{
	return intensity;
}
void Light::setIntensity(glm::vec4 i)
{
	intensity = i;
}

glm::vec3 Light::getDirection()
{
	return direction;
}
void Light::setDirection(glm::vec3 dir)
{
	direction = dir;
}

bool Light::isPointLight()
{
	return isPoint;
}

bool Light::isLightOn()
{
	return isON;
}
void Light::changeLightState()
{
	if (isON)
		isON = false;
	else
		isON = true;
}