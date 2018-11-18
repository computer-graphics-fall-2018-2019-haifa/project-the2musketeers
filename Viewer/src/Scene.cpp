#include "Scene.h"
#include "MeshModel.h"
#include <string>


Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

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

const std::shared_ptr<MeshModel>& Scene::getActiveModel() const
{
	int index = GetActiveModelIndex();
	return getModeli(index);
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




const float Scene::getScale() const {
	if (models.size() < 1)
		return 1.0;
	int index = GetActiveModelIndex();
	return models[index]->getscale();
}


const bool Scene::getReflextX() const {
	if (models.size() == 0)
		return 0;
	int index = GetActiveModelIndex();
	return models[index]->getreflextX();
}

const bool Scene::getReflextY() const { 
	if (models.size() == 0)
		return 0;
	int index = GetActiveModelIndex();
	return models[index]->getreflextY();
}

const bool Scene::getReflextZ() const {
	if (models.size() == 0)
		return 0;
	int index = GetActiveModelIndex();
	return models[index]->getreflextZ();
}

void Scene::setScale(const float s) 
{
	if (models.size() == 0)
		return;
	int index = GetActiveModelIndex();
	if (s < 0.001)
		models[index]->setscale(0.001f);
	else if (s > 2000.0f)
		models[index]->setscale(2000.0f);
	else
		models[index]->setscale(s);

}

void Scene::changeReflextX(bool a) {
	if (models.size() == 0)
		return ;
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextX(a);
}

void Scene::changeReflextY(bool a) {
	if (models.size() == 0)
		return ;
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextY(a);
}

void Scene::changeReflextZ(bool a) { 
	if (models.size() == 0)
		return ;
	int index = GetActiveModelIndex();
	models[index]->ChangeReflextZ(a);
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

const float Scene::getRotationX() const
{
	if (models.size() == 0) return 0;
	int index = GetActiveModelIndex();
	return models[index]->getRotationX();
}
const float Scene::getRotationY() const
{
	if (models.size() == 0) return 0;
	int index = GetActiveModelIndex();
	return models[index]->getRotationY();
}

const float Scene::getRotationZ() const
{
	if (models.size() == 0) return 0;
	int index = GetActiveModelIndex();
	return models[index]->getRotationZ();
}

void Scene::setRotationX(float a)
{
	if (1) return;

	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	return models[index]->setRotationX(a);
}

void Scene::setRotationY(float a)
{
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();

	return models[index]->setRotationY(a);
}

void Scene::setRotationZ(float a)
{
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	return models[index]->setRotationZ(a);
}

void Scene::setTranslationVector(glm::vec3 v)
{
	if (models.size() == 0) return;
	int index = GetActiveModelIndex();
	models[index]->setTranslationVector(v);
}

 glm::vec3 Scene::getTranslationVector() const
{
	if (models.size() == 0) return glm::vec3(1.0,1.0,1.0);
	int index = GetActiveModelIndex();
	return models[index]->getTranslationVector();
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


