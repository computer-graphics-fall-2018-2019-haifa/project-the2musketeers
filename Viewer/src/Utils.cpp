#include "Utils.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)



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

	int facesNumber = faces.size();
	for (int i = 0; i < facesNumber; i++)
	{
		glm::vec3 v1 = vertices[faces[i].GetVertexIndex(0) - 1];
		glm::vec3 v2 = vertices[faces[i].GetVertexIndex(1) - 1];
		glm::vec3 v3 = vertices[faces[i].GetVertexIndex(2) - 1];

		glm::vec3 vn1 = normals[faces[i].GetNormalIndex(0) - 1];
		glm::vec3 vn2 = normals[faces[i].GetNormalIndex(1) - 1];
		glm::vec3 vn3 = normals[faces[i].GetNormalIndex(2) - 1];
		faces[i].setFaceCenter(v1, v2, v3);
		faces[i].setFaceNormal(vn1, vn2, vn3);
	}
	int vertNumber = vertices.size();
	std::vector<glm::vec3> verticesNormals;
	std::vector<int> vert2;

	verticesNormals.resize(vertNumber, v3(0, 0, 0));
	vert2.resize(vertNumber, 0);
	int faceSize = faces.size();
	for (int i = 0; i < faceSize; i++)
	{
		const Face& face = faces[i];
		int v1Index = face.GetVertexIndex(0);
		int v2Index = face.GetVertexIndex(1);
		int v3Index = face.GetVertexIndex(2);
		const v3& p1 = vertices[v1Index - 1];
		const v3& p2 = vertices[v2Index - 1];
		const v3& p3 = vertices[v3Index - 1];
		int n1Index = face.GetNormalIndex(0);
		int n2Index = face.GetNormalIndex(1);
		int n3Index = face.GetNormalIndex(2);

		verticesNormals[v1Index - 1] += normals[n1Index - 1];
		vert2[v1Index - 1]++;
		verticesNormals[v2Index - 1] += normals[n2Index - 1];
		vert2[v2Index - 1]++;
		verticesNormals[v3Index - 1] += normals[n3Index - 1];
		vert2[v3Index - 1]++;
	}
	for (int i = 0; i < vertNumber; i++)
	{
		verticesNormals[i] /= vert2[i];
	}

	MeshModel model =  MeshModel(faces, vertices, normals, verticesNormals, Utils::GetFileName(filePath));
	float scale = 1.0;
	float x = mx.x-mn.x , y = mx.y - mn.y, z = mx.z - mn.z;
	scale = (y > x) ? y : x;
	if (z > scale)
		scale = z;

//	model.objectchange(Utils::getTranslateMatrix(glm::vec3(-(mn.x + mx.x) / 2.0f, -(mn.y + mx.y) / 2.0f, -(mn.z + mx.z) / 2.0f)));
//	model.objectchange(Utils::getScaleMatrix(2.0f/scale, 2.0f / scale, 2.0f / scale));

	
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

float Utils::getVectorNormal(const v3& w)
{
	float normal = sqrtf(w.x*w.x + w.y*w.y + w.z*w.z);
	return normal;
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



float Utils::triangle_area(v3 a,v3 b,v3 c){ return fabsf((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0f); }








void Utils::blur(float* buf, int n, int m)
{
	float* tmp = new float[3 * n*m];
	int i, j;


	for (i = 0; i < (n*m * 3 - 1); i++)
		tmp[i] = buf[i];

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < m - 1; j++)
		{
			buf[INDEX(n, i, j, 0)] = calc_blur(tmp, n, m, i, j, 0);
			buf[INDEX(n, i, j, 1)] = calc_blur(tmp, n, m, i, j, 1);
			buf[INDEX(n, i, j, 2)] = calc_blur(tmp, n, m, i, j, 2);
		}
	}
	delete[] tmp;
	return;
}


float Utils::calc_blur(float* buf, int n, int m, int i, int j, int rgb)
{
	float res = 0.1621*buf[INDEX(n, i, j, rgb)];
	if (i > 0 && j > 0)
	{
		res += 0.0596*buf[INDEX(n, i - 1, j - 1, rgb)]; //(i-1,j-1)
		if (i > 1 && j > 1)
			res += 0.0030*buf[INDEX(n, i - 2, j - 2, rgb)]; //(i-2,j-2)
	}

	if (i < n-1 && j < m-1)
	{
		res += 0.0596*buf[INDEX(n, i + 1, j + 1, rgb)];//(i+1,j+1)
		if (i< n-2 && j <m-2)
			res += 0.0030*buf[INDEX(n, i + 2, j + 2, rgb)];//(i+2,j+2)
	}

	if (i > 0)
	{
		res += 0.0983*buf[INDEX(n, i -1, j, rgb)];//(i-1,j)
		if(j>1)
			res += 0.0133*buf[INDEX(n, i - 1, j-2, rgb)];//(i-1,j-2)
		if (j < m-2)
			res += 0.0133*buf[INDEX(n, i - 1, j + 2, rgb)];//(i-1,j+2)
		if (i > 1) {
			res += 0.0216*buf[INDEX(n, i - 2, j, rgb)];//(i-2,j)
			if(j>0)
				res += 0.0133*buf[INDEX(n, i - 2, j - 1, rgb)];//(i-2,j-1)
			if(j<m-1)
				res += 0.0133*buf[INDEX(n, i - 2, j + 1, rgb)];//(i-2,j+1)
		}
	}


	if (j < m - 1)
	{
		res += 0.0983*buf[INDEX(n, i, j + 1, rgb)];//(i,j+1)
		if (j < m - 2)
			res += 0.0216*buf[INDEX(n, i, j + 2, rgb)];//(i,j+2)
	}

	if (j > 0 )
	{
		res += 0.0983*buf[INDEX(n, i, j - 1, rgb)];//(i,j-1)
		if (j > 1)
			res += 0.0216*buf[INDEX(n, i, j - 2, rgb)];//(i,j-2)
	}

	if (i > 0 && j < m - 1)
	{
		res += 0.0596*buf[INDEX(n, i - 1, j + 1, rgb)];//(i-1,j+1)
		if (i > 1 && j < m - 2)
			res += 0.0030*buf[INDEX(n, i-2, j + 2, rgb)];//(i-2,j+2)
	}

	if (i < n-1 && j > 0)
	{
		res += 0.0596*buf[INDEX(n, i + 1, j - 1, rgb)];//(i+1,j-1)
		if (i < n-2 && j > 1)
			res += 0.0030*buf[INDEX(n, i + 2, j - 2, rgb)];//(i+2,j-2)
	}


	if (i < n-1)
	{
		res += 0.0983*buf[INDEX(n, i + 1, j, rgb)];//(i+1,j)
		if (j > 1)
			res += 0.0133*buf[INDEX(n, i + 1, j - 2, rgb)];//(i+1,j-2)
		if (j < m - 2)
			res += 0.0133*buf[INDEX(n, i + 1, j + 2, rgb)];//(i+1,j+2)
		if (i < n-2) {
			res += 0.0216*buf[INDEX(n, i + 2, j, rgb)];//(i+2,j)
			if (j > 0)
				res += 0.0133*buf[INDEX(n, i + 2, j - 1, rgb)];//(i+2,j-1)
			if (j < m - 1)
				res += 0.0133*buf[INDEX(n, i + 2, j + 1, rgb)];//(i+2,j+1)
		}
	}

	return res;
}



void Utils::bloom_combine(float* original, float* blured_lights, int n, int m)
{
	int i, j;
	float t;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
		{
			t = blured_lights[INDEX(n, i, j, 0)] + blured_lights[INDEX(n, i, j, 1)] + blured_lights[INDEX(n, i, j, 2)];
			if (t != 0.00f)
			{
				original[INDEX(n, i, j, 0)] += blured_lights[INDEX(n, i, j, 0)];
				original[INDEX(n, i, j, 1)] += blured_lights[INDEX(n, i, j, 1)];
				original[INDEX(n, i, j, 2)] += blured_lights[INDEX(n, i, j, 2)];

				original[INDEX(n, i, j, 0)] *= 0.50f;
				original[INDEX(n, i, j, 1)] *= 0.50f;
				original[INDEX(n, i, j, 2)] *= 0.50f;
			}
		}
	}
	return;
}



 float* Utils::bloom_threshold(float* original, int n, int m)
{
	 float* t = new float[3 * n*m];
	 int i, j;
	 for (i = 0; i < n; i++)
	 {
		 for (j = 0; j < m; j++)
		 {
			 t[INDEX(n, i, j, 0)] = 0.00f;
			 t[INDEX(n, i, j, 1)] = 0.00f;
			 t[INDEX(n, i, j, 2)] = 0.00f;
		 }
	 }


	 for (i = 0; i < n; i++)
	 {
		 for (j = 0; j < m; j++)
		 {
			 if (original[INDEX(n, i, j, 0)] > 0.9 || original[INDEX(n, i, j, 1)] > 0.9 || original[INDEX(n, i, j, 2)] > 0.9)
			 {
				 t[INDEX(n, i, j, 0)] = original[INDEX(n, i, j, 0)];
				 t[INDEX(n, i, j, 1)] = original[INDEX(n, i, j, 1)];
				 t[INDEX(n, i, j, 2)] = original[INDEX(n, i, j, 2)];
			 }
		 }
	 }
	 return t;
}


 void Utils::bloom(float* buf, int n, int m)
{
	 float* lights = Utils::bloom_threshold(buf, n, m);
	 Utils::blur(lights, n, m);
	 Utils::bloom_combine(buf, lights, n, m);
	 delete[] lights;
	 return;
}

