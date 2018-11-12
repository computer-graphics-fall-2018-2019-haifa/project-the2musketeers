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



}

void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{


}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetZoom(const float zoom)
{

}



m4 LookAt(const v3& eye, const v3& at, const v3& up)
{
	v3 z = Utils::normalize(eye - at);
	v3 x = Utils::cross_product(up, z);
	v3 y = Utils::cross_product(z, x);
	x = Utils::normalize(x);
	y = Utils::normalize(y);
	return m4(
		x.x, x.y, x.z, -Utils::dot_product(x, eye),
		y.x, y.y, y.z, -Utils::dot_product(y, eye),
		z.x, z.y, z.z, -Utils::dot_product(z, eye),
		0, 0, 0, 1);
}