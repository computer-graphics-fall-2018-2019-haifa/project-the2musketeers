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


		ImGui::Text("Model sittings");

		if (scene.GetModelCount()) {
			if (ImGui::Button("Change Active Model")) 
				scene.SetActiveModelIndex((scene.GetActiveModelIndex() + 1) % scene.GetModelCount());


			bool bnbox = scene.GetBoundingBox();
			ImGui::Checkbox("Draw Bounding Box", &bnbox);
			scene.setBoundingBox(bnbox);

			const std::shared_ptr<MeshModel>& model = scene.getActiveModel();


			float scx = 1;
			float scy = 1;
			float scz = 1;
			float scall = 1;
			ImGui::SliderFloat("Scale by x", &scx, 0.01f, 30.0f);
			ImGui::SliderFloat("Scale by y", &scy, 0.01f, 30.0f);
			ImGui::SliderFloat("Scale by z", &scz, 0.01f, 30.0f);
			ImGui::SliderFloat("Scale by all axis", &scall, 0.01f, 30.0f);

			model->objectchange(Utils::getScaleMatrix(scx,1,1));
			model->objectchange(Utils::getScaleMatrix(1, scy, 1));
			model->objectchange(Utils::getScaleMatrix(1, 1, scz));
			model->objectchange(Utils::getScaleMatrix(scall, scall, scall));
			

	

			float x_rotate = 0;
			float y_rotate = 0;
			float z_rotate = 0;
			

			ImGui::Text("Local Rotations");
			ImGui::SliderAngle("Rotate X", &x_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Y", &y_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Z", &z_rotate, -360, 360);
			glm::mat4x4 xMat,yMat,zMat;
			xMat = Utils::getRotateMatrixBy_x(x_rotate);
			yMat = Utils::getRotateMatrixBy_y(y_rotate);
			zMat = Utils::getRotateMatrixBy_z(z_rotate);

			model->objectchange(xMat);
			model->objectchange(yMat);
			model->objectchange(zMat);



			x_rotate = 0;
			y_rotate = 0;
			z_rotate = 0;


			ImGui::Text("World Rotations");
			ImGui::SliderAngle("Rotate X", &x_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Y", &y_rotate, -360, 360);
			ImGui::SliderAngle("Rotate Z", &z_rotate, -360, 360);
			xMat = Utils::getRotateMatrixBy_x(x_rotate);
			yMat = Utils::getRotateMatrixBy_y(y_rotate);
			zMat = Utils::getRotateMatrixBy_z(z_rotate);

			model->worldchange(xMat);
			model->worldchange(yMat);
			model->worldchange(zMat);



			float tx = 0;
			float ty = 0;
			float tz = 0;
			ImGui::Text("Translations");
			ImGui::SliderFloat("Translate by x", &tx, -2.000f, 2.000f);
			ImGui::SliderFloat("Translate by y", &ty, -2.000f, 2.000f);
			ImGui::SliderFloat("Translate by z", &tz, -2.000f, 2.000f);

			model->worldchange(Utils::getTranslateMatrix(glm::vec3(tx,ty,tz)));


		}

















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