#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>


/*
 * Renderer class.
 */
class Renderer
{
private:
	float *colorBuffer;
	float *zBuffer;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;

	void putPixel(int x, int y, const glm::vec3& color);
	void createBuffers(int viewportWidth, int viewportHeight);

	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();

	void Render(Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void Draw_Line_Bresenham(float x1, float y1, float z1, float x2, float y2,float z2, glm::vec3& Color,bool flip=0);
	void matsav_zevel_Bresenham(float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3& Color); //when slope less than -1
	// Add more methods/functionality as needed...
	void DrawTriangleOnScreen(const v3& a, const v3& b, const v3& c, v3& color);
	void drawFaces(const Scene& scene, m4 matrix);
	
	const v3 applyTransformations(const v3& point,const Scene& scene);
	//const v3 applyTransformations(const v4& point);
	m4 getTransformationsMatrix(const Scene& scene);


	void drawCamera(Scene& scene, Camera camera, glm::mat4 matrix);

	float calc_min(float a, float b, float c, float d);
	float calc_max(float a, float b, float c, float d);
};
