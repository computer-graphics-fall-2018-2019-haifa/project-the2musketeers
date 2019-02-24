#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>
#include <iostream>
#include "Light.h"

using namespace std;

bool showDemoWindow = false;
bool showCameraSittings = false;
bool showColorSittings = false;
static bool mod_cont = 0;
static bool AddParLight = 0;
static bool AddPointLight = 0;
//static float Light[3] = { 0,0,0 };


static bool localFrame = 1;
static bool worldFrame = 0;


glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor() {return clearColor;}

glm::vec4 VertNormalsColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);
const glm::vec4& GetVertNormalsColor() {return VertNormalsColor;}
glm::vec4 FaceNormalsColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);
const glm::vec4& GetFaceNormalsColor() { return FaceNormalsColor; }

v4 mColor = v4(0, 0, 0, 0);

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// Main window
	{

		ImGui::Begin("Settings");

		//////////////////////////////////////////////////////////////
		ImGui::Text("*****************************************************");
		ImGui::Text("Clera Colour: ");
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		ImGui::Text("*****************************************************");

		ImGui::Text("Light Settings: ");
		glm::vec4 ambColour = scene.getAmbientIntensity();
		ImGui::ColorEdit3("Ambient Intensity", (float*)&ambColour);
		scene.setAmbientIntensity(ambColour);

		if (scene.getLightCount() > 0)
		{
			Light& activeLight = scene.getActiveLight();
			v3 actvLightParameter; // = direction or position
			if (activeLight.isPointLight())
			{
				actvLightParameter = activeLight.getPosition();
				ImGui::InputFloat3("Light Position", (float*)&actvLightParameter, 3);
				activeLight.setPosition(actvLightParameter);
			}
			else
			{
				actvLightParameter = activeLight.getDirection();
				ImGui::InputFloat3("Light Direction", (float*)&actvLightParameter, 3);
				activeLight.setDirection(actvLightParameter);
			}
			v4 LightColor = activeLight.getIntensity(); //  = get active light color
			ImGui::ColorEdit3("Light Intensity", (float*)&LightColor);
			activeLight.setIntensity(LightColor);

			//set active light color
			bool OnOff = activeLight.isLightOn(); // = light is on or off
			char* onof = "OFF";
			if (OnOff)
				onof = "ON";
			if (ImGui::Button(onof))
				activeLight.changeLightState();
		}
/*
		//shading:
		static int shading = 0; // = get shading
		if (shading==2) {
			if (ImGui::Button("Phong shading")) {
				shading = 0;
				//set shading to flat
			}
		}
		else {
			if (shading == 1) {
				if (ImGui::Button("gouraud shading")) {
					shading = 2;
					//set shading to phong
				}
			}
			else {
				if (ImGui::Button("Flat shading")) {
					shading = 1;
					//set shading to gouraud
				}
			}
		}
		*/

//		if (ImGui::Button("Delete Active Light")) {		}
		static bool newlight = 0;
		if (ImGui::Button("Add new Light")) {
			newlight = 1;
		}
		



		ImGui::Text("*****************************************************");

		//////////////////////////////////////////////////////////////////////////////////////////////
		ImGui::Text("Camera Settings");

		if (scene.GetCameraCount()) {
			if (ImGui::Button("Change Active Camera")) {
				scene.SetActiveCameraIndex((scene.GetActiveCameraIndex() + 1) % scene.GetCameraCount());
			}
			Camera& c = scene.getActiveCamera();
			static float Far = c.getFar();
			static float Near = c.getNear();
			static float fov_angle_rad = c.getFovy();
			static float height = 0.0f;
			static bool projection = 0;


			if (ImGui::Button("change projection"))
				projection = !projection;
			if (projection) {
				ImGui::Text("Orthographic:\n\n");
				ImGui::SliderFloat("Height", &height, 0.0f, 200.0f);
			}
			else {
				ImGui::Text("prespective:\n\n");
				ImGui::SliderAngle("Fovy", &fov_angle_rad, 1.0f, 110.0f);
			}
			ImGui::SliderFloat("Near", &Near, -100.0f, 100.0f);
			ImGui::SliderFloat("Far", &Far, -100.0f, 100.0f);
			

			c.setFar(Far);
			c.setNear(Near);
			c.setFovy(fov_angle_rad);
			//c.SetPerspectiveProjection(fov_angle_rad, 1280.0 / 720.0, Near, Far);
		}
		ImGui::Text("*****************************************************");
		///////////////////////////////////////////////////////////////////////////////////////////////////


		ImGui::Text("Model Settings");

		if (scene.GetModelCount()) {
			if (ImGui::Button("Change Active Model")) 
				scene.SetActiveModelIndex((scene.GetActiveModelIndex() + 1) % scene.GetModelCount());



			const std::shared_ptr<MeshModel>& model = scene.getActiveModel();

			mColor = model->GetColor();
//			std::cout << mColor.x << " " << mColor.y << " " << mColor.z << " " << mColor.w << std::endl;
			ImGui::ColorEdit3("MeshModel Color", (float*)&mColor);
			model->SetColor(mColor);


			ImGui::Checkbox("Local Frame", &localFrame);
			if (localFrame == 0)
				worldFrame = 1;
			else
				worldFrame = 0;
			ImGui::Checkbox("World Frame", &worldFrame);
			if (worldFrame == 1)
				localFrame = 0;
			else
				localFrame = 1;
			if (localFrame)
			{
				float scx = 1;
				float scy = 1;
				float scz = 1;
				float scall = 1;
				ImGui::SliderFloat("Scale by x", &scx, 0.900f, 1.100f);
				ImGui::SliderFloat("Scale by y", &scy, 0.900f, 1.100f);
				ImGui::SliderFloat("Scale by z", &scz, 0.900f, 1.100f);
				ImGui::SliderFloat("Scale by all axis", &scall, 0.900f, 1.100f);

				model->objectchange(Utils::getScaleMatrix(scx, 1.0f, 1.0f));
				model->objectchange(Utils::getScaleMatrix(1.0f, scy, 1.0f));
				model->objectchange(Utils::getScaleMatrix(1.0f, 1.0f, scz));
				model->objectchange(Utils::getScaleMatrix(scall, scall, scall));




				float x_rotate = 0;
				float y_rotate = 0;
				float z_rotate = 0;


				ImGui::Text("Local Rotations");
				ImGui::SliderAngle("Rotate X", &x_rotate, -10, 10);
				ImGui::SliderAngle("Rotate Y", &y_rotate, -10, 10);
				ImGui::SliderAngle("Rotate Z", &z_rotate, -10, 10);
				glm::mat4x4 xMat, yMat, zMat;
				xMat = Utils::getRotateMatrixBy_x(x_rotate);
				yMat = Utils::getRotateMatrixBy_y(y_rotate);
				zMat = Utils::getRotateMatrixBy_z(z_rotate);

				model->objectchange(xMat);
				model->objectchange(yMat);
				model->objectchange(zMat);

			}
			if (worldFrame)
			{
				float x_rotate2 = 0;
				float y_rotate2 = 0;
				float z_rotate2 = 0;

				ImGui::Text("World Rotations");
				ImGui::SliderAngle("Rotate X2", &x_rotate2, -10, 10);
				ImGui::SliderAngle("Rotate Y2", &y_rotate2, -10, 10);
				ImGui::SliderAngle("Rotate Z2", &z_rotate2, -10, 10);
				model->worldchange(Utils::getRotateMatrixBy_x(x_rotate2));
				model->worldchange(Utils::getRotateMatrixBy_y(y_rotate2));
				model->worldchange(Utils::getRotateMatrixBy_z(z_rotate2));



				float tx = 0;
				float ty = 0;
				float tz = 0;
				ImGui::Text("Translations");
				ImGui::SliderFloat("Translate by x", &tx, -2.000f, 2.000f);
				ImGui::SliderFloat("Translate by y", &ty, -2.000f, 2.000f);
				ImGui::SliderFloat("Translate by z", &tz, -2.000f, 2.000f);

				model->worldchange(Utils::getTranslateMatrix(glm::vec3(tx, ty, tz)));

			}

		}



		if (newlight)
		{
			ImGui::Begin("New Light");
			static v3 position = v3(0, 0, 0);
			static v3 direction = v3(0, 0, 0);
			static v4 Lcolor;
			static bool poi = 1;
			static bool par = 0;

			ImGui::Checkbox("Point Light", &poi);
			if (poi == 0)
				par = 1;
			else
				par = 0;
			ImGui::Checkbox("Parallel Light", &par);
			if (par == 1)
				poi = 0;
			else
				poi = 1;

			
			ImGui::ColorEdit3("New Light intensity", (float*)&Lcolor);
			if(poi)
				ImGui::InputFloat3("New Light Position", (float*)&position, 3);
			else
				ImGui::InputFloat3("New Light Direction", (float*)&direction, 3);
			
			
			if (ImGui::Button("ADD")) 
			{
				newlight = 0;
				Light newLight;

				if (poi)
					newLight = Light(position, Lcolor, true);
				else
					newLight = Light(direction, Lcolor, false);

				scene.AddLight(newLight);
			}
			ImGui::End();
		}













		ImGui::Text("*****************************************************");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}




	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}