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
	glm::vec4 color;
	std::string modelName;

	float Scale = 10.0f;
	bool reflect_by_x = 0;
	bool reflect_by_y = 0;
	bool reflect_by_z = 0;
	float rotationX = 0.0f;
	float rotationY = 0.0f;
	float rotationZ = 0.0f;
	glm::vec3 translationCords = glm::vec3(220.0, 120.0, 100.0);

public:
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

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


	const float getscale() const;
	void setscale(const float s);

	const bool getreflextX() const;
	const bool getreflextY() const;
	const bool getreflextZ() const;

	void ChangeReflextX(bool a);
	void ChangeReflextY(bool a);
	void ChangeReflextZ(bool a);

	const float getRotationX() const;
	const float getRotationY() const;
	const float getRotationZ() const;

	void setRotationX(float a);
	void setRotationY(float a);
	void setRotationZ(float a);

	glm::vec3 getTranslationVector() const;
	void setTranslationVector(glm::vec3 v);
	// Add more methods/functionality as needed...
};
