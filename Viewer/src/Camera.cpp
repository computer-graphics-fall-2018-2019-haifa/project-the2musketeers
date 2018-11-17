#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>




Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera() {}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
//	m4 LookAtMatrix = Camera::LookAt(eye, at, up);



}

void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{	
	projectionTransformation=m4(2/(aspectRatio * height), 0, 0, 0, 0, 2/height, 0, 0, 0, 0, 2/(near-far), 0, 0, 0, 0, 1); 
}


void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{
	float s =( 1 / ((float)tan((fovy*M_PI) / 360.0f)));
	projectionTransformation = m4(s,0,0,0,0,s,0,0,0,0,far/(near-far),-1,0,0,far*near/(near-far),0);
}

void Camera::SetZoom(const float zoom) { this->zoom = zoom; }


/*
m4 Camera::LookAt(const v3& eye, const v3& at, const v3& up)
{
	v3 z = Utils::normalize(eye - at);
	v3 x = Utils::cross_product(up, z);
	v3 y = Utils::cross_product(z, x);
	x = Utils::normalize(x);
	y = Utils::normalize(y);
	m4 m= m4(
		x.x, x.y, x.z, -Utils::dot_product(x, eye),
		y.x, y.y, y.z, -Utils::dot_product(y, eye),
		z.x, z.y, z.z, -Utils::dot_product(z, eye),
		0, 0, 0, 1);
	return m * Utils::getTranslateMatrix(-eye);
}

*/