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
			vertices.push_back(Utils::Vec3fFromStream(issLine));
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

	return MeshModel(faces, vertices, normals, Utils::GetFileName(filePath));
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
	float z = v.z;
	return v3(v.w / z, v.x / z, v.y / z);
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
	return m4(	1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				v.x, v.y, v.z, 1 );
}

m4 Utils::getTranslateMatrix(const float& x, const float& y, const float& z)
{
	return(getTranslateMatrix(v3(x, y, z)));
}

m4 Utils::getRotateMatrixBy_x(const float &a)
{
	return m4(1, 0, 0, 0,
			0, cos(a), sin(a), 0,
			0, -sin(a), cos(a), 0,
			0, 0, 0, 1);
}

m4 Utils::getRotateMatrixBy_y(const float &a)
{
	return m4(cos(a), 0, -sin(a), 0,
		0, 1, 0, 0,
		sin(a), 0, cos(a), 0,
		0, 0, 0, 1);
}

m4 Utils::getRotateMatrixBy_z(const float &a)
{
	return m4(cos(a), sin(a), 0, 0,
		-sin(a), cos(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
} 


m4 Utils::ReflectAxis(AX c)
{
	if (c = x)
		return m4(-1, 0, 0, 0,    0, 1, 0, 0,    0, 0, 1, 0,    0, 0, 0, 1);
	if (c = y)
		return m4(1, 0, 0, 0,    0, -1, 0, 0,    0, 0, 1, 0,    0, 0, 0, 1);
	if (c = z)
		return m4(1, 0, 0, 0,    0, 1, 0, 0,    0, 0, -1, 0,    0, 0, 0, 1);
}