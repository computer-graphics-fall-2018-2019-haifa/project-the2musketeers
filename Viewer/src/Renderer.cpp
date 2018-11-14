#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include "ImguiMenus.h"
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3* viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}

void Renderer::Render(const Scene& scene)
{
	drawFaces(scene);
	//DrawTriangle(50, 50, 50, 200, 130, 200);
	//Draw_Line_Bresenham(100, 1000, 300, 50, glm::vec3(1, 0, 0));
	//#############################################
	//## You should override this implementation ##
	//## Here you should render the scene.       ##
	//#############################################

	// Draw a chess board in the middle of the screen
	/*for (int i = 100; i < viewportWidth - 100; i++)
	{
		for (int j = 100; j < viewportHeight - 100; j++)
		{
			int mod_i = i / 50;
			int mod_j = j / 50;

			int odd = (mod_i + mod_j) % 2;
			if (odd)
			{
				putPixel(i, j, glm::vec3(0, 1, 0));
			}
			else
			{
				putPixel(i, j, glm::vec3(1, 0, 0));
			}
		}
	}*/
	
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Renderer::Draw_Line_Bresenham(int x1, int y1, int x2, int y2,glm::vec3& Color,bool flip)
{
	
	if (x1 > x2) {
		Draw_Line_Bresenham(x2, y2, x1, y1, Color);
		return;
	}
	if (x1 == x2) {
		int yMin=(y2>y1?y1:y2),yMax=(y2>y1?y2:y1);
		while (yMin <= yMax) {
			putPixel(x1, yMin, Color);
			yMin++;
		}
		return;
	}

	int dx=(x2 - x1);
	int dy = abs(y2 - y1);
	float a = ((float)dy/(float)dx);
	int x = x1, y = y1;

	if (a == 0.0f) {
		while (x <= x2) {
			putPixel(x, y1, Color);
			x++;
		}
		return;
	}
	if ((a > 1.0f)) {
		if (y2 < y1) {
			matsav_zevel_Bresenham(x1, y1, x2, y2, Color);
			return;
		}
		Draw_Line_Bresenham(y1, x1, y2, x2, Color,1);
		return;
	}
	int e = -dx;
	while (x <= x2) {
		if (e > 0) {
			y++;
			e -= (2 * dx);
		}
		if (y2 > y1) {
			if (flip)
				putPixel(y, x, Color);
			else
				putPixel(x, y, Color);
		}
		else {
			putPixel(x, y1 - (y - y1), Color);
		}
		x++;
		e += (2 * dy);
		
	}return;

}


void Renderer::matsav_zevel_Bresenham(int x1, int y1, int x2, int y2, glm::vec3& Color) {
	int dy = y1 - y2;
	int dx = x2 - x1;
	int x = x1, y = y1;
	int e = -dy;
	while (y >= y2) {
		if (e > 0) {
			x++;
			e -= (2 * dy);
		}
		putPixel(x, y, Color);
		y--;
		e += (2 * dx);
	}return;
}

void Renderer::DrawTriangleOnScreen(const v3& a, const v3& b, const v3& c, v3& color)
{
	int x1 = a.x, x2= b.x, x3= c.x,
		y1= a.y, y2 = b.y, y3 = c.y;
/*
	x1 += 320;
	x2 += 320;
	x3 += 320;
	y1 += 180;
	y2 += 180;
	y3 += 180;
*/
	Renderer::Draw_Line_Bresenham(x1, y1, x2, y2,color);
	Renderer::Draw_Line_Bresenham(x1, y1, x3, y3, color);
	Renderer::Draw_Line_Bresenham(x3, y3, x2, y2, color);

}

void Renderer::drawFaces(const Scene& scene)
{
	if (scene.GetModelCount() == 0)
		return;
//	Draw_Line_Bresenham(10, 20, 20, 40, v3(1, 0, 0));

	int modelIndex = scene.GetActiveModelIndex();
	const std::shared_ptr<MeshModel>& model = scene.getModeli(modelIndex);

//	const std::vector<Face>& faces = model->getFaces;
	for (int i = 0; i < model->getFacesNumber(); i++)
	{
		const Face& face = model->getFaceI(i);
		int v1Index = face.GetVertexIndex(0);
		int v2Index = face.GetVertexIndex(1);
		int v3Index = face.GetVertexIndex(2);
		const v3& p1 = model->getVertixI(v1Index - 1);
		const v3& p2 = model->getVertixI(v2Index - 1);
		const v3& p3 = model->getVertixI(v3Index - 1);

		v3 tP1 = applyTransformations(p1,scene);
		v3 tP2 = applyTransformations(p2,scene);
		v3 tP3 = applyTransformations(p3,scene);

		v4 c = scene.getColor();
		v3 col = v3(c.x, c.y, c.z);

		Renderer::DrawTriangleOnScreen(tP1, tP2, tP3, col);
	}

}


const v3 Renderer::applyTransformations(const v3& point, const Scene& scene)
{
	float scale = scene.getScale();
//	float scale = scene.getScale();
	v4 p = Utils::swtitch_to_hom(point);
	p = Utils::getScaleMatrix(v3(scale, scale, scale))*p;
	
	float angleY = scene.getRotationY();
	float angleX = scene.getRotationX();
	p = Utils::getRotateMatrixBy_y(angleY)*p;
	p = Utils::getRotateMatrixBy_x(angleX)*p;

	if(scene.getReflextX())
		p = Utils::ReflectAxis('x')*p;
	if (scene.getReflextY())
		p = Utils::ReflectAxis('y')*p;
	if (scene.getReflextZ())
		p = Utils::ReflectAxis('z')*p;
	p = Utils::getTranslateMatrix(v3(520, 380, 100))*p;

	return Utils::back_from_hom(p);
}
/*
const v3 Renderer::applyTransformations(const v4& point)
{
	return Utils::back_from_hom(Utils::getTranslateMatrix(v3(500, 500, 500)) * point);
	return Utils::getScaleMatrix(v3(2,2,2))*point;
}
*/