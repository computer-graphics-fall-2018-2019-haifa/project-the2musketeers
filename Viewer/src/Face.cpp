#include "Face.h"

Face::Face(std::istream& issLine)
{
	vertexIndices =  { 0, 0, 0 };
	normalIndices =  { 0, 0, 0 };
	textureIndices = { 0, 0, 0 };

	char c;
	for (int i = 0; i < 3; i++)
	{
		issLine >> std::ws >> vertexIndices.at(i) >> std::ws;

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> std::ws;

		if (issLine.peek() == '/')
		{
			issLine >> c >> std::ws >> normalIndices.at(i);
			continue;
		}
		else
		{
			issLine >> textureIndices.at(i);
		}

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> normalIndices.at(i);
	}
}

Face::~Face()
{

}

int Face::GetVertexIndex(int index) const
{
	return vertexIndices[index];
}

int Face::GetNormalIndex(int index) const
{
	return normalIndices[index];
}

int Face::GetTextureIndex(int index)
{
	return textureIndices[index];
}


void Face::setFaceNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	faceNormal = (p1 + p2 + p3) / 3.000f;

}
void Face::setFaceCenter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	faceCenter = (p1 + p2 + p3) / 3.000f;
}

glm::vec3 Face::getFaceCenter() const
{
	return faceCenter;
}

glm::vec3 Face::getFaceNormal() const
{
	return faceNormal;
}

