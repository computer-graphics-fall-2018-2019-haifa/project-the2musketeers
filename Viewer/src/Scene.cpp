#include "Scene.h"
#include "MeshModel.h"
#include <string>


Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0),
	activeLightIndex(0),
	cameraModel()
{
	//std::string path("C:\\Users\\user\\Documents\\GitHub\\project-the2musketeers\\data\\Camera.obj");
	//cameraModel = Utils::LoadMeshModel(path);
}
MeshModel Scene::getCameraModel()
{
	return cameraModel;
}
 Camera& Scene::getActiveCamera()
{
	return cameras[activeCameraIndex];
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

void Scene::SetActiveLightIndex(int index)
{
	if (index >= 0 && index < lightSources.size())
	{
		activeLightIndex = index;
	}
}

const int Scene::GetActiveLightIndex() const
{
	return activeLightIndex;
}

Light& Scene::getActiveLight()
{
	int index = activeLightIndex;
	return lightSources[index];
	// TODO: insert return statement here
}

Light Scene::getLightI(int i)
{
	if (i >= 0 && i < lightSources.size())
	return lightSources[i];
}

const std::shared_ptr<MeshModel>& Scene::getActiveModel() const
{
	int index = GetActiveModelIndex();
	return getModeli(index);
}

Camera Scene::getCamerai(int index) const
{
	if (index >= 0 && index < cameras.size())
		return cameras[index];
}

const std::shared_ptr<MeshModel>& Scene::getModeli (int index) const
{
	if (index >= 0 && index < models.size())
		return models[index];
	return nullptr;
}

const v4 Scene::getColor(int a) const {
	if (models.size() == 0)
		return v4(0,0,0,0);
	int index = GetActiveModelIndex();
	if(a==0)
		return models[index]->GetColor();
	if(a==1)
		return models[index]->GetVertNormalColor();
	if(a==2)
		return models[index]->GetFaceNormalColor();
}

void Scene::setColor(v4 c,int a) {
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	if (a == 0)
		models[index]->SetColor(c);
	if (a == 1)
		models[index]->SetVertNormalColor(c);
	if (a == 2)
		models[index]->SetFaceNormalColor(c);
}





 void Scene::setBoundingBox(bool a)
 {
	 if (models.size() == 0) return;
	 int index = GetActiveModelIndex();
	 models[index]->setBoundingBox(a);
 }

bool Scene::GetBoundingBox()
 {
	 if (models.size() == 0) return 0;
	 int index = GetActiveModelIndex();
	 return models[index]->GetBoundingBox();
 }
///////////////////////////////////////////////////////////

void Scene::setVertNormals(bool a)
{
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	models[index]->setVertNormals(a);
}

bool Scene::GetVertNormals()
{
	if (models.size() == 0) return 0;
	int index = GetActiveModelIndex();
	return models[index]->GetVertNormals();
}


///////////////////////////////////////////////////


void Scene::setFaceNormals(bool a)
{
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	models[index]->setFaceNormals(a);
}

bool Scene::GetFaceNormals()
{
	if (models.size() == 0) return 0;
	int index = GetActiveModelIndex();
	return models[index]->GetFaceNormals();
}


void Scene::setWorldScale(float s)
{
	if (s < 1.0)
		worldScale = 1.0;
	else
	worldScale = s;
}
float Scene::getWorldScale()
{
	return worldScale;
}

