#pragma once
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"

typedef glm::vec3 v3;
typedef glm::vec4 v4;
typedef glm::mat4 m4;

/*
 * Utils class.
 * This class is consisted of static helper methods that can have many clients across the code.
 */
class Utils
{
public:
	static glm::vec3 Vec3fFromStream(std::istream& issLine);
	static glm::vec2 Vec2fFromStream(std::istream& issLine);
	static MeshModel LoadMeshModel(const std::string& filePath);

	v4 swtitch_to_hom(const v3 &v);
	v3 back_from_hom(const v4 &v);

	m4 getScaleMatrix(const v3 &v);
	m4 getScaleMatrix(const float& x, const float& y, const float& z);

	m4 getRotateMatrixBy_x(const float &a);
	m4 getRotateMatrixBy_y(const float &a);
	m4 getRotateMatrixBy_z(const float &a);

	m4 getTranslateMatrix(const v3 &v);
	m4 getTranslateMatrix(const float& x, const float& y, const float& z);



	// Add here more static utility functions...
	// For example:
	//	1. function that gets an angle, and returns a rotation matrix around a certian axis
	//	2. function that gets a vector, and returns a translation matrix
	//	3. anything else that may be useful in global scope

private:
	static std::string GetFileName(const std::string& filePath);
};
