#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>




Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	_zoom(1.0),_eye(eye),_at(at),_up(up)
{
	_fovy = 0.7;
	_near = 1;
	_far = 10;

	SetCameraLookAt(eye, at, up);
}

Camera::~Camera() {}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	v3 z = Utils::normalize(eye - at);
	v3 x = Utils::normalize(Utils::cross_product(up,z));
	v3 y = Utils::cross_product(z, x);
	y = Utils::normalize(y);
	m4 m = m4(
		x.x, x.y, x.z, 0,
		y.x, y.y, y.z, 0,
		z.x, z.y, z.z, 0,
		0, 0, 0, 1);
	lookAtTransformation =  Utils::getTranslateMatrix(v3(-1,-1,-1)*eye) * m;
}
/*
void Camera::setCameraEye(glm::vec3 newEye)
{
	_eye = newEye;
	SetCameraLookAt(_eye, _at, _up);
}
*/
void Camera::RotateCameraX(float x)
{
	glm::vec4 eye = Utils::swtitch_to_hom(_eye);
	eye = glm::transpose(Utils::getRotateMatrixBy_y(x)) * eye;
	_eye = Utils::back_from_hom(eye);
	SetCameraLookAt(_eye, _at, _up);
}

void Camera::RotateCameraY(float y)
{
	/*
	glm::vec4 eye = Utils::swtitch_to_hom(_eye);
	glm::vec4 up = Utils::swtitch_to_hom(_up);
	glm::mat4 rotate = Utils::getRotateMatrixBy_x(y);

	eye = rotate * eye;
	up = rotate * up;

	_eye = Utils::back_from_hom(eye);
	_up = Utils::back_from_hom(up);

	SetCameraLookAt(_eye, _at, _up);
	*/
}


void Camera::SetOrthographicProjection (
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{	
	m4 S = m4(

	);
	projectionTransformation = m4(
		2.0/(aspectRatio * height), 0, 0, 0,
		0, 2.0/height, 0, 0,
		0, 0, abs(2.0/(near-far)), 0,
		0, 0, 0, 1.0); 
	/*
	projectionTransformation = m4(
		2.0 / (aspectRatio * height), 0, 0, 0,
		0, 2.0 / height, 0, 0,
		0, 0, 2.0 / (near - far), (far + near) / (near - far),
		0, 0, 0, 1.0);
	*/
	m4 temp1 = glm::transpose(projectionTransformation);

	std::cout << temp1[0][0] << " " << temp1[0][1] << " " << temp1[0][2] << " " << temp1[0][3] << std::endl;
	std::cout << temp1[1][0] << " " << temp1[1][1] << " " << temp1[1][2] << " " << temp1[1][3] << std::endl;
	std::cout << temp1[2][0] << " " << temp1[2][1] << " " << temp1[2][2] << " " << temp1[2][3] << std::endl;
	std::cout << temp1[3][0] << " " << temp1[3][1] << " " << temp1[3][2] << " " << temp1[3][3] << std::endl;

}


void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{
//	std::cout << "Fovy: " << fovy << " AR: " << aspectRatio <<
//		" Near: " << near << " Far: " << far << std::endl;

	//	float y = near * tanf(fovy);
//	float x = y * aspectRatio;
	float angle = fovy * M_PI;
	angle = angle / 360;

	angle = tanf(angle/2);
	
	projectionTransformation = m4(
		1.00f/(aspectRatio*(angle)),0,0,0,
		0, 1.00f / (angle),0,0,
		0,0,-(near-far)/(near-far), (2 * near * far) / (near - far),
		0,0,1,0);

	/*
	m4 temp1 = projectionTransformation;

	std::cout << temp1[0][0] << " " << temp1[0][1] << " " << temp1[0][2] << " " << temp1[0][3] << std::endl;
	std::cout << temp1[1][0] << " " << temp1[1][1] << " " << temp1[1][2] << " " << temp1[1][3] << std::endl;
	std::cout << temp1[2][0] << " " << temp1[2][1] << " " << temp1[2][2] << " " << temp1[2][3] << std::endl;
	std::cout << temp1[3][0] << " " << temp1[3][1] << " " << temp1[3][2] << " " << temp1[3][3] << std::endl;
	*/
}

void Camera::SetZoom(const float zoom) { this->_zoom = zoom; }

m4 Camera::getProjectionTransformation() const
{
	return projectionTransformation;
}

m4 Camera::GetCameraLookAt() const
{
	return lookAtTransformation;
}

glm::vec3 Camera::getCameraPosition() {return _eye;}
glm::vec3 Camera::getCameraUp() { return _up; }


float Camera::getFovy() { return _fovy; }
void Camera::setFovy(float newFovy) { _fovy = newFovy; }
float Camera::getNear() { return _near; }
void Camera::setNear(float newNear) { _near = newNear; }
float Camera::getFar() { return _far; }
void Camera::setFar(float newFar) { _far = newFar; }

