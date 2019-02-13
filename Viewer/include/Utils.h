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

	static v4 swtitch_to_hom(const v3 &v);
	static v3 back_from_hom(const v4 &v);

	static m4 getScaleMatrix(const v3 &v);
	static m4 getScaleMatrix(const float& x, const float& y, const float& z);

	static m4 getRotateMatrixBy_x(const float &a);
	static m4 getRotateMatrixBy_y(const float &a);
	static m4 getRotateMatrixBy_z(const float &a);

	static m4 getTranslateMatrix(const v3 &v);
	static m4 getTranslateMatrix(const float& x, const float& y, const float& z);

	static m4 ReflectAxis(char c);

	static float dot_product(const v3 &w, const v3 &n);
	static v3 cross_product(const v3 &w, const v3 &n);
	static m4 rotate_arbitrary_axis(const float& a, const v3& p, const v3& dir);

	static v3 normalize(const v3& w);
	
	static m4 transpose(m4 mat);
	static float Utils::getVectorNormal(const v3& w);

	static float triangle_area(v3 a, v3 b, v3 c);


	static void blur(float* buf, int n, int m);
	static float calc_blur(float* buf, int n, int m, int i, int j, int rgb);

	static void bloom(float* buf, int n, int m);
	static void bloom_combine(float* original, float* blured_lights, int n, int m);
	static float* bloom_threshold(float* original, int n, int m);

	// Add here more static utility functions...
	// For example:
	//	1. function that gets an angle, and returns a rotation matrix around a certian axis
	//	2. function that gets a vector, and returns a translation matrix
	//	3. anything else that may be useful in global scope

private:
	static std::string GetFileName(const std::string& filePath);
};
