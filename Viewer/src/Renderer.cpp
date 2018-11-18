#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include "ImguiMenus.h"
#include <vector>
#include <cmath>
#include <iostream>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportWidth/2, viewportHeight/2);
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

void Renderer::Render(Scene& scene)
{
//	m4 matrix = getTransformationsMatrix(scene);
//	Draw_Line_Bresenham(0, 0, 100, 100, v3(1, 0, 0));

	const std::shared_ptr<MeshModel>& model = scene.getActiveModel();
	if (model == nullptr)
		return;
//	model->MultiplyWorldTransformation(Utils::getTranslateMatrix(model->getTranslationVector()));
//	model->setTranslationVector(v3(0, 0, 0));
	if (model->getreflextX())
		model->MultiplyWorldTransformation(Utils::ReflectAxis('x'));
	if (model->getreflextY())
		model->MultiplyWorldTransformation(Utils::ReflectAxis('y'));
	if (model->getreflextZ())
		model->MultiplyWorldTransformation(Utils::ReflectAxis('z'));

	model->ChangeReflextX(false);
	model->ChangeReflextY(false);
	model->ChangeReflextZ(false);

//	float scale = model->getscale();
//	model->MultiplyWorldTransformation(Utils::getScaleMatrix(v3(scale, scale, scale)));
//	model->setscale(1.0);

	float angleY = model->getRotationY();
	float angleX = model->getRotationX();
	model->MultiplyWorldTransformation(glm::transpose(Utils::getRotateMatrixBy_x(angleX)));

	model->MultiplyWorldTransformation(glm::transpose(Utils::getRotateMatrixBy_y(angleY)));

	model->setRotationX(0.0);
	model->setRotationY(0.0);
	float scale = model->getscale();
	//	model->MultiplyWorldTransformation(Utils::getScaleMatrix(v3(scale, scale, scale)));
	//	model->MultiplyWorldTransformation(Utils::getTranslateMatrix(model->getTranslationVector()));
//	model->setTranslationVector(v3(0, 0, 0));

	m4 matrix = //Utils::getTranslateMatrix(model->getTranslationVector()) *
		glm::transpose(Utils::getScaleMatrix(v3(scale, scale, scale))) *
		model->GetWorldTransformation();

	//	Camera camera = Camera(v3(0, 0, 2),v3(0, 0, 0), v3(0, 1, 0));
//	scene.AddCamera(camera);
//	Camera activeCamera = scene.getActiveCamera();
//	scene.getActiveCamera().SetOrthographicProjection(3.5,1280/720.0,5,1);


	m4 lookat = scene.getActiveCamera().GetCameraLookAt();
	m4 projectionMatrix = scene.getActiveCamera().getProjectionTransformation();


	lookat = glm::inverse(lookat);

	projectionMatrix = glm::transpose(projectionMatrix);
	lookat = glm::transpose(lookat);
	matrix = glm::transpose(matrix);
	matrix =
		projectionMatrix *
		lookat *
		matrix;
	/*
		m4 temp1 = matrix;
		std::cout << temp1[0][0] << " " << temp1[0][1] << " " << temp1[0][2] << " " << temp1[0][3] << std::endl;
		std::cout << temp1[1][0] << " " << temp1[1][1] << " " << temp1[1][2] << " " << temp1[1][3] << std::endl;
		std::cout << temp1[2][0] << " " << temp1[2][1] << " " << temp1[2][2] << " " << temp1[2][3] << std::endl;
		std::cout << temp1[3][0] << " " << temp1[3][1] << " " << temp1[3][2] << " " << temp1[3][3] << std::endl;
		matrix =
			glm::transpose(matrix);
		matrix =
			glm::transpose(Utils::getTranslateMatrix(v3(500, 300, 0))) *
	//		glm::transpose(projectionMatrix) *
			lookat *
			matrix;
	//	matrix = glm::transpose(matrix);

		std::cout << std::endl;
		temp1 = matrix;
		std::cout << temp1[0][0] << " " << temp1[0][1] << " " << temp1[0][2] << " " << temp1[0][3] << std::endl;
		std::cout << temp1[1][0] << " " << temp1[1][1] << " " << temp1[1][2] << " " << temp1[1][3] << std::endl;
		std::cout << temp1[2][0] << " " << temp1[2][1] << " " << temp1[2][2] << " " << temp1[2][3] << std::endl;
		std::cout << temp1[3][0] << " " << temp1[3][1] << " " << temp1[3][2] << " " << temp1[3][3] << std::endl;
	*/

	matrix = glm::transpose(Utils::getTranslateMatrix(v3(500, 300, 0))) * matrix;
	drawFaces(scene, matrix);
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

	Renderer::Draw_Line_Bresenham(x1, y1, x2, y2,color);
	Renderer::Draw_Line_Bresenham(x1, y1, x3, y3, color);
	Renderer::Draw_Line_Bresenham(x3, y3, x2, y2, color);

}

void Renderer::drawFaces(const Scene& scene, m4 matrix)
{
	if (scene.GetModelCount() == 0)
		return;


	int modelIndex = scene.GetActiveModelIndex();
	const std::shared_ptr<MeshModel>& model = scene.getModeli(modelIndex);

	v4 col;

	float min_x = 5000.0, min_y = 5000.0, min_z = 5000.0; //for the bounding box
	float max_x = -5000.0, max_y = -5000.0, max_z = -5000.0;
	bool draw_bounding = model->GetBoundingBox();
	bool draw_vert_normals = model->GetVertNormals();
	bool draw_face_normals = model->GetFaceNormals();

	
	int vertNumber = model->getVerticesNumber();
	std::vector<v3> vert1;
	std::vector<int> vert2;

	if (draw_vert_normals) {
		vert1.clear();
		vert2.clear();
		vert1.resize(vertNumber, v3(0, 0, 0));
		vert2.resize(vertNumber, 0);

	}
	

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

		
		if (draw_bounding) {
			min_x = calc_min(min_x, p1.x, p2.x, p3.x);
			min_y = calc_min(min_y, p1.y, p2.y, p3.y);
			min_z = calc_min(min_z, p1.z, p2.z, p3.z);

			max_x = calc_max(max_x, p1.x, p2.x, p3.x);
			max_y = calc_max(max_y, p1.y, p2.y, p3.y);
			max_z = calc_max(max_z, p1.z, p2.z, p3.z);
		}

		int n1Index = face.GetNormalIndex(0);
		int n2Index = face.GetNormalIndex(1);
		int n3Index = face.GetNormalIndex(2);
		if (draw_vert_normals) {
			vert1[v1Index-1]+= model->getNormalI(n1Index-1);
			vert2[v1Index-1]++;
			vert1[v2Index-1] += model->getNormalI(n2Index-1);
			vert2[v2Index-1]++;
			vert1[v3Index-1] += model->getNormalI(n3Index-1);
			vert2[v3Index-1]++;
		}

		
		if (draw_face_normals) {
			v3 face_n = (model->getNormalI(n1Index - 1) + model->getNormalI(n2Index - 1) + model->getNormalI(n3Index - 1)) / 3.0f;
			v3 center_of_face = (p1 + p2 + p3) / 3.0f;
			face_n += center_of_face;
			center_of_face = Utils::back_from_hom(matrix*Utils::swtitch_to_hom(center_of_face));
			face_n= Utils::back_from_hom(matrix*Utils::swtitch_to_hom(face_n));
			col = scene.getColor(2);
			v3 c= v3(col.x, col.y, col.z);
			Renderer::Draw_Line_Bresenham(center_of_face.x, center_of_face.y, face_n.x, face_n.y, c);

		}


		v4 hp1 = Utils::swtitch_to_hom(p1);
		v4 hp2 = Utils::swtitch_to_hom(p2);
		v4 hp3 = Utils::swtitch_to_hom(p3);
		hp1 = matrix * hp1;
		hp2 = matrix * hp2;
		hp3 = matrix * hp3;


		

		col = scene.getColor(0);
		v3 c = v3(col.x, col.y, col.z);
		Renderer::DrawTriangleOnScreen(Utils::back_from_hom(hp1), Utils::back_from_hom(hp2)
			, Utils::back_from_hom(hp3), c);



		


	}


	//now time to draw vertex normals
	if (draw_vert_normals) {
		col = scene.getColor(1);
		v3 c = v3(col.x, col.y, col.z);
		for (int i = 0; i < vertNumber; i++) {
			v3 p = model->getVertixI(i);
			vert1[i] = vert1[i] / (float)vert2[i];
			vert1[i] += p;
			vert1[i] =Utils::back_from_hom(matrix*Utils::swtitch_to_hom(vert1[i]));
			p= Utils::back_from_hom(matrix*Utils::swtitch_to_hom(p));
			Renderer::Draw_Line_Bresenham(p.x, p.y, vert1[i].x, vert1[i].y, c);
		}
	}

	vert1.clear();
	vert2.clear();


	// now time to draw bounding box
	if (draw_bounding) {
		v4 p1 = v4(min_x, min_y, min_z,1);
		v4 p2 = v4(max_x, min_y, min_z,1);
		v4 p3 = v4(min_x, max_y, min_z,1);
		v4 p4 = v4(max_x, max_y, min_z,1);
		v4 p5 = v4(min_x, min_y, max_z,1);
		v4 p6 = v4(max_x, min_y, max_z,1);
		v4 p7 = v4(min_x, max_y, max_z,1);
		v4 p8 = v4(max_x, max_y, max_z,1);

		p1 = matrix * p1;
		p2 = matrix * p2;
		p3 = matrix * p3;
		p4 = matrix * p4;
		p5 = matrix * p5;
		p6 = matrix * p6;
		p7 = matrix * p7;
		p8 = matrix * p8;

		v3 bhp1 = Utils::back_from_hom(p1);
		v3 bhp2 = Utils::back_from_hom(p2);
		v3 bhp3 = Utils::back_from_hom(p3);
		v3 bhp4 = Utils::back_from_hom(p4);
		v3 bhp5 = Utils::back_from_hom(p5);
		v3 bhp6 = Utils::back_from_hom(p6);
		v3 bhp7 = Utils::back_from_hom(p7);
		v3 bhp8 = Utils::back_from_hom(p8);
		col = scene.getColor(0);
		v3 coll = v3(col.x, col.y, col.z);

		Renderer::Draw_Line_Bresenham(bhp1.x, bhp1.y, bhp2.x, bhp2.y, coll);
		Renderer::Draw_Line_Bresenham(bhp1.x, bhp1.y, bhp3.x, bhp3.y, coll);
		Renderer::Draw_Line_Bresenham(bhp4.x, bhp4.y, bhp2.x, bhp2.y, coll);
		Renderer::Draw_Line_Bresenham(bhp4.x, bhp4.y, bhp3.x, bhp3.y, coll);

		Renderer::Draw_Line_Bresenham(bhp5.x, bhp5.y, bhp6.x, bhp6.y, coll);
		Renderer::Draw_Line_Bresenham(bhp5.x, bhp5.y, bhp7.x, bhp7.y, coll);
		Renderer::Draw_Line_Bresenham(bhp6.x, bhp6.y, bhp8.x, bhp8.y, coll);
		Renderer::Draw_Line_Bresenham(bhp7.x, bhp7.y, bhp8.x, bhp8.y, coll);

		Renderer::Draw_Line_Bresenham(bhp1.x, bhp1.y, bhp5.x, bhp5.y, coll);
		Renderer::Draw_Line_Bresenham(bhp2.x, bhp2.y, bhp6.x, bhp6.y, coll);
		Renderer::Draw_Line_Bresenham(bhp3.x, bhp3.y, bhp7.x, bhp7.y, coll);
		Renderer::Draw_Line_Bresenham(bhp4.x, bhp4.y, bhp8.x, bhp8.y, coll);
	}
}


float Renderer::calc_min(float a, float b, float c, float d)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	if (d < a)
		a = d;
	return a;
}

float Renderer::calc_max(float a, float b, float c, float d)
{
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	if (d > a)
		a = d;
	return a;
}


/*
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

m4 Renderer::getTransformationsMatrix(const Scene& scene)
{
	m4 transformationsMatrix = m4(
		1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1
	);

	transformationsMatrix *= Utils::getTranslateMatrix(scene.getTranslationVector());
	if(scene.getReflextX())
		transformationsMatrix *= Utils::ReflectAxis('x');
	if (scene.getReflextY())
		transformationsMatrix *= Utils::ReflectAxis('y');
	if (scene.getReflextX())
		transformationsMatrix *= Utils::ReflectAxis('z');


	float scale = scene.getScale();
	transformationsMatrix *= Utils::getScaleMatrix(v3(scale, scale, scale));

	float angleY = scene.getRotationY();
	float angleX = scene.getRotationX();
	transformationsMatrix *= Utils::getRotateMatrixBy_y(angleY);
	transformationsMatrix *= Utils::getRotateMatrixBy_x(angleX);

	return transformationsMatrix;

}
*/