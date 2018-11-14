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



<<<<<<< HEAD
const float Scene::getScale() const {
	int index = GetActiveModelIndex();
	return models[index]->getscale();
}

void Scene::setScale(const float s) { 
	int index = GetActiveModelIndex();
	return models[index]->setscale(s);
}

const bool Scene::getReflextX() const {
	int index = GetActiveModelIndex();
	return models[index]->getreflextX();
}

const bool Scene::getReflextY() const { 
	int index = GetActiveModelIndex();
	return models[index]->getreflextY();
}

const bool Scene::getReflextZ() const {
	int index = GetActiveModelIndex();
	return models[index]->getreflextZ();
=======
const float Scene::getScale() const { return scale; }
void Scene::setScale(const float s) 
{
	if (s < 0.001)
		scale = 0.001;
	else if (s > 2000.0f)
		scale = 2000.0f;
	else
		scale = s;
>>>>>>> 4344099eb10b60dbbec08a9bf8aa498a2425ab9b
}

void Scene::changeReflextX(bool a) {
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextX(a);
}

void Scene::changeReflextY(bool a) {
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextY(a);
}

void Scene::changeReflextZ(bool a) { 
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextZ(a);
}

	
const v4 Scene::getColor() const {
	int index = GetActiveModelIndex();
	return models[index]->GetColor();
}

void Scene::setColor(v4 c) {
	int index = GetActiveModelIndex();
	models[index]->SetColor(c);
}


