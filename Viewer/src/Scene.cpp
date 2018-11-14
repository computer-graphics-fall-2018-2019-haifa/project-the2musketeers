#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
//	SetActiveModelIndex(models.size() - 1);
}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;

	}
	return;
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}

const Camera& Scene::getCamerai(int index) const
{
	if (index >= 0 && index < models.size())
		return cameras[index];
}

const std::shared_ptr<MeshModel>& Scene::getModeli (int index) const
{
	if (index >= 0 && index < models.size())
		return models[index];
	return nullptr;
}



const float Scene::getScale() const { return scale; }
void Scene::setScale(const float s) 
{
	if (s < 0.001)
		scale = 0.001;
	else if (s > 2000.0f)
		scale = 2000.0f;
	else
		scale = s;
}



const bool Scene::getReflextX() const { return reflect_by_x; }
const bool Scene::getReflextY() const { return reflect_by_y; }
const bool Scene::getReflextZ() const { return reflect_by_z; }

void Scene::changeReflextX(bool a) { reflect_by_x = a; }
void Scene::changeReflextY(bool a) { reflect_by_y = a; }
void Scene::changeReflextZ(bool a) { reflect_by_z = a; }
	


const v4 Scene::getColor() const { return color; }
void Scene::setColor(v4 c) { color = c; }