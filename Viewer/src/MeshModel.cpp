#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel() {};

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec3>& verticesNormals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)),
	objectTransform(glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)),
	faces(faces),
	vertices(vertices),
	normals(normals),
	verticesNormals(verticesNormals),
	color(v4(0,0,0,1.00f))
{

}

MeshModel::~MeshModel()
{

}

const float MeshModel::getAbmientConstanst() const
{
	return ambientK;
}

const float MeshModel::getDiffuseConstanst() const
{
	return diffuseK;
}

const float MeshModel::getSpecularConstanst() const
{
	return specularK;
}

void MeshModel::setAmbientConstant(const float k)
{
	if(k >= 0.00f && k <= 1.00f)
		ambientK = k;
}

void MeshModel::setDiffuseConstanst(const float k)
{
	if (k >= 0.00f && k <= 1.00f)
		diffuseK = k;
}

void MeshModel::setSpecularConstanst(const float k)
{
	if (k >= 0.00f && k <= 1.00f)
		specularK = k;
}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return color;
}

const std::string& MeshModel::GetModelName()
{
	return modelName;
}

const std::vector<Face>& MeshModel::getFaces() const
{
	return this->faces;
}

const std::vector<glm::vec3>& MeshModel::getVertices() const
{
	return this->vertices;
}
const std::vector<glm::vec3>& MeshModel::getNormals() const
{
	return this->normals;
}


void MeshModel::MultiplyWorldTransformation(const glm::mat4x4& matrix)
{
	this->worldTransform = worldTransform *matrix;
}


const glm::vec3& MeshModel::getVertixI(int index) const
{
	if(index>=0 && index < vertices.size())
		return vertices[index];
}
const glm::vec3& MeshModel::getNormalI(int index)const
{
	if (index >= 0 && index < normals.size())
		return normals[index];
}
const glm::vec3 & MeshModel::getVertexNormalI(int index) const
{
	if (index >= 0 && index < verticesNormals.size())
		return verticesNormals[index];
}
const Face& MeshModel::getFaceI(int index) const
{
	if (index >= 0 && index < faces.size())
		return faces[index];
}

int MeshModel::getFacesNumber()
{
	return faces.size();
}

int MeshModel::getVerticesNumber()
{
	return vertices.size();
}
int MeshModel::getNormalsNumber()
{
	return normals.size();
}







const glm::vec4& MeshModel::GetVertNormalColor() const { return VertNormalsColor; }
void MeshModel::SetVertNormalColor(const glm::vec4& color) { VertNormalsColor = color; }

const glm::vec4& MeshModel::GetFaceNormalColor() const { return faceNormalsColor; }
void MeshModel::SetFaceNormalColor(const glm::vec4& color) { faceNormalsColor = color; }

void MeshModel::setBoundingBox(bool a) { DrawBoundingBox = a; }
bool MeshModel::GetBoundingBox() { return DrawBoundingBox; }


void MeshModel::setVertNormals(bool a) { DrawVertNormals = a; }
bool MeshModel::GetVertNormals() { return DrawVertNormals; }

void MeshModel::setFaceNormals(bool a) { DrawFaceNormals = a; }
bool MeshModel::GetFaceNormals() { return DrawFaceNormals; }


void MeshModel::objectchange(glm::mat4x4 k) { objectTransform = objectTransform * k; }
void MeshModel::worldchange(glm::mat4x4 k) { worldTransform = worldTransform * k; }

glm::mat4x4 MeshModel::getLocalTransformation() { return objectTransform; }
glm::mat4x4 MeshModel::getWorldTransformation() { return worldTransform; }


