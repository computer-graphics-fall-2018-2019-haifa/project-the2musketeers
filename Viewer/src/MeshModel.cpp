#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1)),
	faces(faces),
	vertices(vertices),
	normals(normals),
	color(v4(0,0,0,0))
{
}

MeshModel::~MeshModel()
{

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






const float MeshModel::getscale() const { return Scale; }
void MeshModel::setscale(const float s) { Scale = s; }

const bool MeshModel::getreflextX() const { return reflect_by_x; }
const bool MeshModel::getreflextY() const { return reflect_by_y; }
const bool MeshModel::getreflextZ() const { return reflect_by_z; }

void MeshModel::ChangeReflextX(bool a) { reflect_by_x = a; }
void MeshModel::ChangeReflextY(bool a) { reflect_by_y = a; }
void MeshModel::ChangeReflextZ(bool a) { reflect_by_z = a; }

const float MeshModel::getRotationX() const { return rotationX; }
const float MeshModel::getRotationY() const { return rotationY; }
const float MeshModel::getRotationZ() const { return rotationZ; }

void MeshModel::setRotationX(float a) { rotationX = a; }
void MeshModel::setRotationY(float a) { rotationY = a; }
void MeshModel::setRotationZ(float a) { rotationZ = a; }
