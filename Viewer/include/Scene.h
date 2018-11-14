#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"




/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;

	int activeCameraIndex;
	int activeModelIndex;

	float Scale=10.0f;
	bool reflect_by_x = 0;
	bool reflect_by_y = 0;
	bool reflect_by_z = 0;
	v4 color = v4(1, 0, 0, 0);

public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& model);
	const int GetModelCount() const;

	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;

	const std::shared_ptr<MeshModel>& getModeli(int index) const;
	const Camera& getCamerai(int index) const;

	const float getScale() const;
	void setScale(const float s);

	const bool getReflextX() const;
	const bool getReflextY() const;
	const bool getReflextZ() const;

	void changeReflextX(bool a);
	void changeReflextY(bool a);
	void changeReflextZ(bool a);


	const v4 getColor() const;
	void setColor(v4 c);

	// Add more methods as needed...
};