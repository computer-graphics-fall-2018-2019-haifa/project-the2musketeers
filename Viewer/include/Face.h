#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>


class Face
{
private:
	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	glm::vec3 faceNormal;
	glm::vec3 faceCenter;
public:
	Face(std::istream& issLine);
	virtual ~Face();
	int Face::GetVertexIndex(int index) const ;
	int Face::GetNormalIndex(int index) const;
	int Face::GetTextureIndex(int index);

	glm::vec3 getFaceNormal() const;
	glm::vec3 getFaceCenter() const;

	void setFaceNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	void setFaceCenter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

};