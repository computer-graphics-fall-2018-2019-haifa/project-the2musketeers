#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform;
	glm::mat4x4 objectTransform;
	glm::vec4 color;
	glm::vec4 VertNormalsColor;
	glm::vec4 faceNormalsColor;
	std::string modelName;
	

	bool DrawVertNormals = 0;
	bool DrawFaceNormals = 0;
	bool DrawBoundingBox = 0;

	float Scale = 360.0f;
	bool reflect_by_x = 0;
	bool reflect_by_y = 0;
	bool reflect_by_z = 0;
	float rotationX = 0.0f;
	float rotationY = 0.0f;
	float rotationZ = 0.0f;
	glm::vec3 translationCords = glm::vec3(0, 0, 0);

public:
	MeshModel();
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const glm::vec4& GetVertNormalColor() const;
	void SetVertNormalColor(const glm::vec4& color);

	const glm::vec4& GetFaceNormalColor() const;
	void SetFaceNormalColor(const glm::vec4& color);

	void setBoundingBox(bool a);
	bool GetBoundingBox();

	void setVertNormals(bool a);
	bool GetVertNormals();

	void setFaceNormals(bool a);
	bool GetFaceNormals();

	void MeshModel::MultiplyWorldTransformation(const glm::mat4x4& matrix);


	const std::string& GetModelName();

	const std::vector<Face>& getFaces() const;
	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<glm::vec3>& getNormals() const;

	const glm::vec3& getVertixI(int index)const;
	const glm::vec3& getNormalI(int index)const;
	const Face& getFaceI(int index) const;

	int getFacesNumber();
	int getVerticesNumber();
	int getNormalsNumber();


	void objectchange(glm::mat4x4 k);
	void worldchange(glm::mat4x4 k);

	glm::mat4x4 objectMat();
	glm::mat4x4 worldMat();

	// Add more methods/functionality as needed...
};
