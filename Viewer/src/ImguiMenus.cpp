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
bool showAnotherWindow = false;



glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor() {return clearColor;}









glm::vec4 NormalsColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);

const glm::vec4& GetNormalsColor() {return NormalsColor;}








void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float Far = 10.0f;
		static float Near = 1.0f;
		static float fov_angle_rad = 0.0f;
		static int counter = 0;


		float sc = scene.getScale();
		

		// 3 bool for reflecting axis
		bool x = scene.getReflextX() ;
		bool y = scene.getReflextY();
		bool z = scene.getReflextZ();


		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &showAnotherWindow);

		ImGui::SliderAngle("Fovy", &fov_angle_rad, 0, 180);
		ImGui::SliderFloat("Near", &Near, 1.0f, 10.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Far", &Far, 1.0f, 10.0f);
		ImGui::SliderFloat("Scale", &sc, 0.01f, 2000.0f);
		scene.setScale(sc);
		
		ImGui::Checkbox("Reflext by X", &x);
		ImGui::Checkbox("Reflext by Y", &y);
		ImGui::Checkbox("Reflext by Z", &z);

		scene.changeReflextX(x);
		scene.changeReflextY(y);
		scene.changeReflextZ(z);

		v4 ModelColor = scene.getColor();
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color
		ImGui::ColorEdit3("Model Color", (float*)&ModelColor);
		scene.setColor(ModelColor);
		ImGui::ColorEdit3("Normal color", (float*)&NormalsColor);
		

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}









	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
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