#include "Utils.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



glm::vec3 Utils::Vec3fFromStream(std::istream& issLine)
{
	float x, y, z;
	issLine >> x >> std::ws >> y >> std::ws >> z;
	return glm::vec3(x, y, z);
}

glm::vec2 Utils::Vec2fFromStream(std::istream& issLine)
{
	float x, y;
	issLine >> x >> std::ws >> y;
	return glm::vec2(x, y);
}



MeshModel Utils::LoadMeshModel(const std::string& filePath)
{
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::ifstream ifile(filePath.c_str());

	std::cout << filePath << std::endl;

	bool isFirstVertex = true;
	glm::vec3 mx, mn;

	// while not end of file
	while (!ifile.eof())
	{
		// get line
		std::string curLine;
		std::getline(ifile, curLine);

		// read the type of the line
		std::istringstream issLine(curLine);
		std::string lineType;

		issLine >> std::ws >> lineType;

		// based on the type parse data
		if (lineType == "v")
		{
			glm::vec3 newVertex = Utils::Vec3fFromStream(issLine);
			vertices.push_back(newVertex);
			if (isFirstVertex == true)
			{
				mn.x = newVertex.x;
				mx.x = newVertex.x;
				mn.y = newVertex.y;
				mx.y = newVertex.y;
				mn.z = newVertex.z;
				mx.z = newVertex.z;
				isFirstVertex = false;
			}
			if (newVertex.x > mx.x)
				mx.x = newVertex.x;
			if (newVertex.x < mn.x)
				mn.x = newVertex.x;

			if (newVertex.x > mx.y)
				mx.y = newVertex.y;
			if (newVertex.y < mn.y)
				mn.y = newVertex.y;

			if (newVertex.z > mx.z)
				mx.z = newVertex.z;
			if (newVertex.z < mn.z)
				mn.z = newVertex.z;
		}
		else if (lineType == "vn")
		{
			normals.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vt")
		{
			// Texture coordinates
		}
		else if (lineType == "f")
		{
			faces.push_back(Face(issLine));
		}
		else if (lineType == "#" || lineType == "")
		{
			// comment / empty line
		}
		else
		{
			std::cout << "Found unknown line Type \"" << lineType << "\"";
		}
	}

	MeshModel model =  MeshModel(faces, vertices, normals, Utils::GetFileName(filePath));
	float scale = 1.0;
	float x = mn.x, y = mn.y, z = mn.z;
	if (abs(mx.x) > abs(mn.x))
		x = abs(mx.x);
	if (abs(mx.y) > abs(mn.y))
		y = abs(mx.y);
	if (abs(mx.z) > abs(mn.z))
		z = abs(mx.z);
	scale = x;
	if (y > scale)
		scale = y;
	if (z > scale)
		scale = z;

	model.setscale(1.0/scale);
//	model.setscale(200);
	return model;
}

std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}






v4 Utils::swtitch_to_hom(const v3 &v)
{
	return v4(v.x, v.y, v.z, 1);
}

v3 Utils::back_from_hom(const v4 &v)
{
	float w = v.w;
	return v3(v.x / w, v.y / w, v.z / w);
}




m4 Utils::getScaleMatrix(const v3 &v)
{
	return m4(	v.x, 0, 0, 0,
				0, v.y, 0, 0,
				0, 0, v.z, 0,
				0, 0, 0, 1 );
}

m4 Utils::getScaleMatrix(const float& x, const float& y, const float& z)
{
	return(getScaleMatrix(v3(x, y, z)));
}


m4 Utils::getTranslateMatrix(const v3 &v)
{
	return m4(	1, 0, 0, v.x,
				0, 1, 0, v.y,
				0, 0, 1, v.z,
				0,0,0, 1 );
}

m4 Utils::getTranslateMatrix(const float& x, const float& y, const float& z)
{
	return(getTranslateMatrix(v3(x, y, z)));
}

m4 Utils::getRotateMatrixBy_x(const float &a)

{
	return m4(
		1, 0, 0, 0,
		0, cosf(a), -sinf(a), 0,
		0, sinf(a), cosf(a), 0,
		0, 0, 0, 1);
}

m4 Utils::getRotateMatrixBy_y(const float &a)
{
	return m4(
		cosf(a), 0, sinf(a), 0,
		0, 1, 0, 0,
		-sinf(a), 0, cosf(a), 0,
		0, 0, 0, 1);
}

m4 Utils::getRotateMatrixBy_z(const float &a)
{
	return m4(cosf(a), sinf(a), 0, 0,
		-sinf(a), cosf(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
} 


m4 Utils::ReflectAxis(char c)
{
	if (c == 'x')
		return m4(-1, 0, 0, 0,    0, 1, 0, 0,    0, 0, 1, 0,    0, 0, 0, 1);
	if (c == 'y')
		return m4(1, 0, 0, 0,    0, -1, 0, 0,    0, 0, 1, 0,    0, 0, 0, 1);
	if (c == 'z')
		return m4(1, 0, 0, 0,    0, 1, 0, 0,    0, 0, -1, 0,    0, 0, 0, 1);
}


float Utils::dot_product(const v3 &w, const v3 &n)
{
	return( (w.x * n.x)+ (w.y * n.y)+ (w.z * n.z));
}


v3 Utils::cross_product(const v3 &w, const v3 &n)
{
	float x = w.y * n.z - w.z * n.y;
	float y = (- w.x * n.z + w.z * n.x);
	float z = w.x * n.y - w.y * n.x;
	return v3(x, y, z);
}


m4 Utils::rotate_arbitrary_axis(const float& a, const v3& p, const v3& dir)
{
	float 
		x = dir.x - p.x,
		y = dir.y - p.y,
		z = dir.z - p.z;

	float
		xAngle = asinf(z / sqrtf(x * x + y * y + z * z)),
		yAngle = acosf(y / sqrtf(x * x + y * y));

	v3 w = Utils::back_from_hom(Utils::getScaleMatrix(v3(-1, -1, -1))*Utils::swtitch_to_hom(p));
	m4 M = Utils::getRotateMatrixBy_y(-yAngle)*Utils::getRotateMatrixBy_x(-xAngle)*Utils::getTranslateMatrix(w);
	m4 invM = Utils::getTranslateMatrix(p)*Utils::getRotateMatrixBy_x(xAngle)*Utils::getRotateMatrixBy_y(yAngle);
	return invM * Utils::getRotateMatrixBy_z(a)*M;


}


v3 Utils::normalize(const v3& w)
{
	float normal = sqrtf(w.x*w.x + w.y*w.y + w.z*w.z);
	if (normal == 0)
		return w;
	return v3(w.x / normal, w.y / normal, w.z / normal);
}

m4 Utils::transpose(m4 mat)
{
	m4 newMatrix(1);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newMatrix[i][j] = mat[j][i];
		}
	}
	return newMatrix;
}