#include "Light.h"



Light::Light()
{
	position = glm::vec3(0,0,0);
	intensity = glm::vec4(0,0,0,0);
	direction = glm::vec3(0,0,0);
	type = Point;
	state = ON;
}

Light::Light(glm::vec3 vector3, glm::vec4 i, LightType type)
{
	if (type == Point)
	{
		position = vector3;
	}
	else
	{
		direction = vector3;
	}

	intensity = i;
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