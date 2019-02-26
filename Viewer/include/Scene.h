#pragma once
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"
#include "Light.h"




/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	MeshModel cameraModel;
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;
	std::vector<Light> lightSources;


	int activeCameraIndex;
	int activeModelIndex;
	int activeLightIndex;

	float worldScale = 1.0f;
	int shadingType;
	bool blur;
	bool bloomEffect;

public:
	Scene();
	MeshModel getCameraModel();
	void AddModel(const std::shared_ptr<MeshModel>& model);
	const int GetModelCount() const;

	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void AddLight(Light& light);
	void delteActiveLight();
	const int getLightCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;

	void SetActiveLightIndex(int index);
	const int GetActiveLightIndex() const;

	Light& getActiveLight();
	Light getLightI(int i);
	void nextLight();

	const int getShadingType() const;
	void setShadingType(int t);

	const bool blurState() const;
	const bool bloomState() const;
	void changeBlurState();
	void changeBloomState();


	const std::shared_ptr<MeshModel>& getActiveModel() const;

	const std::shared_ptr<MeshModel>& getModeli(int index) const;

	 Camera& getActiveCamera();
	Camera getCamerai(int index) const;

	const float getScale() const;
	void setScale(const float s);

	const bool getReflextX() const;
	const bool getReflextY() const;
	const bool getReflextZ() const;

	void changeReflextX(bool a);
	void changeReflextY(bool a);
	void changeReflextZ(bool a);


	const v4 getColor(int a) const;
	void setColor(v4 c,int a);

	const float getRotationX() const;
	const float getRotationY() const;
	const float getRotationZ() const;

	void setRotationX(float a);
	void setRotationY(float a);
	void setRotationZ(float a);

	 glm::vec3 getTranslationVector() const;
	void setTranslationVector(glm::vec3 v);



	void setBoundingBox(bool a);
	bool GetBoundingBox();

	void setVertNormals(bool a);
	bool GetVertNormals();

	void setFaceNormals(bool a);
	bool GetFaceNormals();

	void setWorldScale(float s);
	float getWorldScale();
	// Add more methods as needed...
};