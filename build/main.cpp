#define _USE_MATH_DEFINES
#include <iostream>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "ImguiMenus.h"

// Function declarations
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


static double yOff = 0;

int main(int argc, char ** argv)
{

	int recentDragY = 0;
	// Create GLFW window
	int windowWidth = 1280, windowHeight = 720;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer - the2musketeers");
	if (!window)
	{
		return 1;
	}

	// Move OpenGL context to the newly created window
	glfwMakeContextCurrent(window);

	// Get the current width/height of the frame buffer
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	// Create the renderer and the scene
	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);

	Scene scene = Scene();

	Camera camera1 = Camera(v3(0, 0, -500000), v3(0, 0, 0), v3(0, 1, 0));
	scene.AddCamera(camera1);

	Camera camera2 = Camera(v3(10, 5, 0), v3(0, 0, 0), v3(0, 1, 0));
	scene.AddCamera(camera2);

//	Camera camera2 = Camera(v3(0, 0, -3), v3(0, 0, 0), v3(0, 1, 0));
//	Camera camera3 = Camera(v3(1, 0, 1), v3(0, 0, 0), v3(0, 1, 0));
//	Camera camera4 = Camera(v3(-1, 0, -1), v3(0, 0, 0), v3(0, 1, 0));
//	scene.AddCamera(camera2);
//	scene.AddCamera(camera3);
//	scene.AddCamera(camera4);


	scene.getActiveCamera().SetOrthographicProjection(1, 1.0, 0, 1);
//	scene.getActiveCamera().SetPerspectiveProjection(20,1.2,5,1);

	Light light = Light(glm::vec3(500, 400, 15000), glm::vec4(1, 1, 1, 1), 1);
	scene.AddLight(light);

	// Setup ImGui
	ImGuiIO& io = SetupDearImgui(window);

	// Register a mouse scroll-wheel callback
	glfwSetScrollCallback(window, ScrollCallback);

	float tester = 0;
	// This is the main game loop..
	int counter = 1;
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		StartFrame();

		const std::shared_ptr<MeshModel>& model = scene.getActiveModel();
		if (model != nullptr)
		{
			if (!io.WantCaptureMouse)
			{
				float currentScale = scene.getWorldScale();
//				if (yOff > 0.0)
					scene.setWorldScale(currentScale + 5 * yOff);
/*
				model->setscale(currentScale + 2 * yOff);
				std::cout << model->getscale() << std::endl;
				std::cout << "#" << counter << ":" << std::endl;
				
				counter++;
				if (counter % 50== 0)
				{
					scene.SetActiveCameraIndex(1 - scene.GetActiveCameraIndex());
					glm::vec3 v = scene.getActiveCamera().getCameraPosition();
					std::cout << v.x << "," << v.y << "," << v.z << std::endl;
				}
				
					model->setRotationY((M_PI * 1/ 180.0));
				scene.getActiveCamera().addToCameraEyeX((M_PI / 180));


				ImVec2 d = ImGui::GetMouseDragDelta(0);
				int x = d.x;
				x %= 360;
				if (x >= 180)
					x = 170;
				else if (x <= -180)
					x = -170;
				if(x!=0)
					scene.getActiveCamera().addToCameraEyeX((x/720.0)*M_PI);
*/


				ImVec2 d = ImGui::GetMouseDragDelta(0);
				scene.getActiveCamera().RotateCameraY((d.y / 500)*M_PI);
				scene.getActiveCamera().RotateCameraX((d.x / 500)*M_PI);

//				float recentAngleY = model->getRotationY();
//				float recentAngleX = model->getRotationX();
//				model->setRotationY(recentAngleY + (d.x / 1000)*M_PI);
//				model->setRotationX(recentAngleX + (d.y / 1000)*M_PI);

			d = ImGui::GetMouseDragDelta(1);
				}

		}
		ImGui::ResetMouseDragDelta(0);
		ImGui::ResetMouseDragDelta(1);
		yOff = 0.0;

		// Here we build the menus for the next frame. Feel free to pass more arguments to this function call
		DrawImguiMenus(io, scene);

		// Render the next frame
		RenderFrame(window, scene, renderer, io);
	}

	// If we're here, then we're done. Cleanup memory.
	Cleanup(window);
	return 0;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

	// Handle mouse scrolling here...
	yOff = yoffset;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	// Render the menus
	ImGui::Render();

	// That's how you get the current width/height of the frame buffer (for example, after the window was resized)
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	// Resize handling here... (a suggestion)
	renderer.SetViewport(frameBufferWidth, frameBufferHeight);

	// Clear the frame buffer
	renderer.ClearColorBuffer(GetClearColor());

	// Render the scene
	renderer.Render(scene);

	// Swap buffers
	renderer.SwapBuffers();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}
