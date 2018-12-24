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

bool showDemoWindow = false;
bool showCameraSittings = false;
bool showColorSittings = false;
static bool mod_cont = 0;


glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor() {return clearColor;}

glm::vec4 VertNormalsColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);
const glm::vec4& GetVertNormalsColor() {return VertNormalsColor;}
glm::vec4 FaceNormalsColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);
const glm::vec4& GetFaceNormalsColor() { return FaceNormalsColor; }

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// Main window
	{

		ImGui::Begin("Sittings");

		////////////////////////////////////////////////////////////////////////////////////////////
		ImGui::Text("*****************************************************");
		ImGui::Text("Color and drawing sittings");
		bool ver = scene.GetVertNormals();
		bool face = scene.GetFaceNormals();
		v4 ModelColor = scene.getColor(0);
		v4 vertNormColor = scene.getColor(1);
		v4 faceNormColor = scene.getColor(2);
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		if (scene.GetModelCount()) {
			ImGui::ColorEdit3("Model Color", (float*)&ModelColor);
			ImGui::Checkbox("Draw Vertix Normals", &ver);
			ImGui::ColorEdit3("Vertix Normal color", (float*)&vertNormColor);
			ImGui::Checkbox("Draw Face Normals", &face);
			ImGui::ColorEdit3("Face Normal color", (float*)&faceNormColor);
			scene.setColor(ModelColor, 0);
			scene.setColor(vertNormColor, 1);
			scene.setColor(faceNormColor, 2);
			scene.setFaceNormals(face);
			scene.setVertNormals(ver);
		}
		ImGui::Text("*****************************************************");

		//////////////////////////////////////////////////////////////////////////////////////////////
		ImGui::Text("Camera Settings");

		if (scene.GetCameraCount()) {
			if (ImGui::Button("Change Active Camera")) {
				scene.SetActiveCameraIndex((scene.GetActiveCameraIndex() + 1) % scene.GetCameraCount());
			}
			static float Far = 10.0f;
			static float Near = 1.0f;
			static float fov_angle_rad = 0.0f;
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
				ImGui::SliderAngle("Fovy", &fov_angle_rad, 0, 180);
			}
			ImGui::SliderFloat("Near", &Near, 1.0f, 10.0f);
			ImGui::SliderFloat("Far", &Far, 1.0f, 10.0f);
			static float l = 2;
		
				ImGui::InputFloat("KK", &l, 2.0f, 0.01f);


		}
		ImGui::Text("*****************************************************");
		///////////////////////////////////////////////////////////////////////////////////////////////////


		ImGui::Text("Model Control");

		if (scene.GetModelCount()) {
			if (ImGui::Button("Change Active Model")) {
				scene.SetActiveModelIndex((scene.GetActiveModelIndex() + 1) % scene.GetModelCount());
			}
			bool bnbox = scene.GetBoundingBox();
			/*float sc = scene.getScale();

			// 3 bool for reflecting axis
			bool x = scene.getReflextX();
			bool y = scene.getReflextY();
			bool z = scene.getReflextZ();

			ImGui::SliderFloat("Scale", &sc, 0.01f, 30.0f);
			scene.setScale(sc);

		

			const std::shared_ptr<MeshModel>& model = scene.getActiveModel();

			float x_rotate = 0;
			float y_rotate = 0;
			float z_rotate = 0;
			
			ImGui::Text("Rotating Axis:");
			ImGui::SliderAngle("Rotate X", &x_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Y", &y_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Z", &z_rotate, -360, 360);
			model->setRotationX(2 * x_rotate * M_PI / 180.0);
			model->setRotationY(2 * y_rotate * M_PI / 180.0);
			model->setRotationZ(2 * z_rotate * M_PI / 180.0);
			*/


			ImGui::Checkbox("Draw Bounding Box", &bnbox);
			scene.setBoundingBox(bnbox);
		}


		ImGui::Text("*****************************************************");
		///////////////////////////////////////////////////////////////////////////////////////////////////


		ImGui::Text("World Control");















		ImGui::Text("*****************************************************");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

/*	help for openning another window:

	bool show_another_window;
	ImGui::Checkbox("open new window", &show_another_window);
	if (show_another window)
	{
		{
		all
		the
		work
		should
		be
		here
		}



		if (ImGui::Button("Close Me"))
		{
			showCameraSittings = false;
		}
		ImGui::End();
	}
*/



	// 4. Demonstrate creating a fullscreen menu bar and populating it.
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