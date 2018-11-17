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


		float sc = scene.getScale();
		

		// 3 bool for reflecting axis
		bool x = scene.getReflextX() ;
		bool y = scene.getReflextY();
		bool z = scene.getReflextZ();


		ImGui::Begin("Sittings");              
		ImGui::Checkbox("Camera Sittings", &showCameraSittings);
		ImGui::Checkbox("Color Sittings", &showColorSittings);

		bool bnbox = scene.GetBoundingBox();
		ImGui::Checkbox("Draw Bounding Box", &bnbox);
		scene.setBoundingBox(bnbox);

		ImGui::SliderFloat("Scale", &sc, 0.01f, 2000.0f);
		scene.setScale(sc);
		



		if (ImGui::Button("Reflect by X"))
			x = !x;

		if (ImGui::Button("Reflect by Y"))
			y = !y;

		if (ImGui::Button("Reflect by Z"))
			z = !z;

		scene.changeReflextX(x);
		scene.changeReflextY(y);
		scene.changeReflextZ(z);

		

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}









	// 3. Show another simple window.
	if (showCameraSittings)
	{
		ImGui::Begin("Camera Sittings", &showCameraSittings); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		
		static float Far = 10.0f;
		static float Near = 1.0f;
		static float fov_angle_rad = 0.0f;
		static float height = 0.0f;
		static bool projection = 0;

		ImGui::Text("Here you can change camera sittings \n \n");

		//ImGui::Checkbox("Orthographic Projection", &Ortho_projection);
		//ImGui::Checkbox("Prespective Projection", !(&Ortho_projection));

		if (ImGui::Button("change projection"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			projection = !projection;
		if (projection) {
			ImGui::Text("Orthographic:\n\n");
			ImGui::SliderFloat("Height", &height, 0.0f, 200.0f);
		}
		else {
			ImGui::Text("prespective:\n\n");
			ImGui::SliderAngle("Fovy", &fov_angle_rad, 0, 180);
		}


		ImGui::SliderFloat("Near", &Near, 1.0f, 10.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Far", &Far, 1.0f, 10.0f);


		if (ImGui::Button("Close Me"))
		{
			showCameraSittings = false;
		}
		ImGui::End();
	}



	if (showColorSittings)
	{
		ImGui::Begin("Color Sittings", &showColorSittings); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		bool ver = scene.GetVertNormals();
		bool face = scene.GetFaceNormals();
		v4 ModelColor = scene.getColor(0);
		v4 vertNormColor = scene.getColor(1);
		v4 faceNormColor = scene.getColor(2);
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		ImGui::ColorEdit3("Model Color", (float*)&ModelColor);
		ImGui::Checkbox("Draw Vertix Normals", &ver);
		ImGui::ColorEdit3("Vertix Normal color", (float*)&vertNormColor);
		ImGui::Checkbox("Draw Face Normals", &face);
		ImGui::ColorEdit3("Face Normal color", (float*)&faceNormColor);
		scene.setColor(ModelColor,0);
		scene.setColor(vertNormColor,1);
		scene.setColor(faceNormColor,2);
		scene.setFaceNormals(face);
		scene.setVertNormals(ver);



		if (ImGui::Button("Close Me"))
		{
			showColorSittings = false;
		}
		ImGui::End();
	}




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