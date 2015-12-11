// Laatija: Niko Kinnunen

#include "Renderer.h"
#include "Camera.h"
#include "FreeType.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define ScreenWidth 1280
#define ScreenHeight 720

Camera camera;
fontData ourData;

Renderer::Renderer()
	: vertexBufferPosition(0), projection(glm::ortho(0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight), 0.f, -1.f, 1.f))
{
	effect.LoadShader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");
}

/*
GLvoid BuildFont(GLvoid)
{
	HDC hDC = NULL;

	GLuint base;


	HFONT font;
	HFONT oldFont;
	base = glGenLists(96);
	font = CreateFont(	-24, 
						0, 
						0, 
						0, 
						FW_BOLD, 
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_ONLY_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE | DEFAULT_PITCH,
						"Times New Roman");
	oldFont = (HFONT)SelectObject(hDC, font);
	wglUseFontBitmaps(hDC, 32, 96, base);
	SelectObject(hDC, oldFont);
	DeleteObject(font);

}

GLvoid KillFont(GLvoid)
{
	glDeleteLists(base, 96);
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	BuildFont();
	ourData.init("Fontit/Dense-regular.TTF", 16);
	return TRUE;
}

GLvoid glPrint(const char *fmt, ...)
{
	
	char text[ 256 ];
	va_list ap;
	if (fmt == NULL)
	{
		return;
	}
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

int DrawGLScene(GLvoid)
{
	float cnt1=0, cnt2=0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f, 0.0f, -1.0f);						// Move One Unit Into The Screen

	// Blue Text
	glColor3ub(0, 0, 0xff);

	// Position The WGL Text On The Screen
	glRasterPos2f(-0.40f, 0.35f);
	

	glColor3ub(0xff, 0, 0);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(cnt1, 0, 0, 1);
	glScalef(1, .8 + .3*cos(cnt1 / 5), 1);
	glTranslatef(-180, 0, 0);
	ourData.print(ourData, 320, 240, "Active FreeType Text - %7.2f", cnt1);
	glPopMatrix();

	//Uncomment this to test out print's ability to handle newlines.
	//freetype::print(our_font, 320, 200, "Here\nthere\nbe\n\nnewlines\n.", cnt1);

	cnt1 += 0.051f;										// Increase The First Counter
	cnt2 += 0.005f;										// Increase The First Counter
	return TRUE;										// Everything Went OK
}
*/

void Renderer::render()
{
	camera.initialize();

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);


	// piirrä, tunge vertexit jne
	for (Sprite* sprite : sprites) 
	{
		// Vasen alanurkka
		VertexPositionColorTexture vertices[4];
		vertices[0] = VertexPositionColorTexture{
			sprite->getPosition(),
			sprite->getColor(),
			glm::vec2(0, 1)
		};
		// Oikea alanurkka
		vertices[1] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth() * sprite->getScale().x, 0),
			sprite->getColor(),
			glm::vec2(1, 1)
		};

		// Vasen ylänurkka
		vertices[2] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(0, sprite->getTexture()->getHeight() * sprite->getScale().y),
			sprite->getColor(),
			glm::vec2(0, 0)
		};
		// Oikea ylänurkka
		vertices[3] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth() * sprite->getScale().x, sprite->getTexture()->getHeight() * sprite->getScale().y),
			sprite->getColor(),
			glm::vec2(1, 0)
		};

		glBufferSubData(
			GL_ARRAY_BUFFER,
			sizeof(VertexPositionColorTexture) * verticesPerSprite * vertexBufferPosition,
			sizeof(vertices),
			vertices
			);
		// liikuta "pointteria" eteenpäin
		vertexBufferPosition++;
	}

	glUseProgram(effect.getProgram());

	// bindaa shaderi
	for (size_t i = 0; i < sprites.size(); i++) {
		Sprite* sprite = sprites[i];
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getId());
		//assert(glGetError() == 0);

		GLuint matrixLocation = glGetUniformLocation(effect.getProgram(), "MVP");
		//assert(glGetError() == 0);

		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawElements(
			GL_TRIANGLES,
			indicesPerSprite,
			GL_UNSIGNED_INT,
			(void*)(indicesPerSprite * i * sizeof(unsigned int))
			);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// unbindaus
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vertexBufferPosition = 0;
}

void Renderer::init()
{
	createIndexBuffer();

	createVertexBuffer();
}

void Renderer::createIndexBuffer()
{
	indices.reserve(indicesPerSprite * initialBufferSize);

	for (unsigned int i = 0; i < initialBufferSize * indicesPerSprite; i += verticesPerSprite)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * indices.size(), // indeksien koko tavuina
		indices.data(),
		GL_STATIC_DRAW
		);
	
	// poistetaan bufferi käytöstä
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::createVertexBuffer()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorTexture)
		* initialBufferSize * 4, nullptr, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));

	// poistetaan bufferi käytöstä
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Renderer::add(Sprite* sprite)
{
	sprites.push_back(sprite);
}

void Renderer::remove(Sprite*)
{

}

Renderer::~Renderer()
{

}