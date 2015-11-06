// Laatija: Niko Kinnunen
#include "Engine.h"
#include "Effect.h"
#include <cassert>
#include <Windows.h>
#include "Texture.h"

Engine::Engine() : isRunning(false), window(nullptr), Window_Width(0), Window_Height(0)
{
}

Engine::~Engine()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Engine::initialize(int Window_Width = 1280, int Window_Height = 720)
{
	std::cout << "Resoluutio " << Window_Width << " x " << Window_Height << std::endl;
	std::cout << "Alustetaan..." << std::endl;
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == NULL);



	//Ikkunan koon muuttamista varten olevaa koodia
	//Toistaiseksi turhaa, voi ignorata.

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//int virtual_width = 1280;
	//int virtual_height = 720;
	//
	//float targetAspectRatio = virtual_width / virtual_height;
	//
	//// figure out the largest area that fits in this resolution at the desired aspect ratio
	//int width = Window_Width;
	//int height = (int)(width / targetAspectRatio + 0.5f);
	//
	//if (height > Window_Height)
	//{
	//	//It doesn't fit our height, we must switch to pillarbox then
	//	height = Window_Height;
	//	width = (int)(height * targetAspectRatio + 0.5f);
	//}
	//
	//// set up the new viewport centered in the backbuffer
	//int vp_x = (Window_Width / 2) - (width / 2);
	//int vp_y = (Window_Height / 2) - (height / 2);
	//
	//glViewport(vp_x, vp_y, width, height);
	//
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//glOrtho(0, Window_Width, Window_Height, 0, -1, 1);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();
	//
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//
	////Now to calculate the scale considering the screen size and virtual size
	//float scale_x = (float)((float)(Window_Width) / (float)virtual_width);
	//float scale_y = (float)((float)(Window_Height) / (float)virtual_height);
	//glScalef(scale_x, scale_y, 1.0f);
	//////////////////////////////////////////////////////////////////////////////////



	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	window = SDL_CreateWindow("Graphics_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Window_Width, Window_Height, SDL_WINDOW_OPENGL);
	assert(window != nullptr);

	context = SDL_GL_CreateContext(window);
	assert(context != nullptr);

	glewExperimental = GL_TRUE;
	const GLenum glewResult = glewInit();
	assert(glewResult == GLEW_OK);


	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	std::cout << "OpenGL context version: " << versionMajor << ", " << versionMinor << std::endl;

	std::cout << std::endl;
	
}

//Onko kolmio piirretty?
bool isDrawn = false;

void Engine::run()
{
	initialize();
	SDL_Event event;
	isRunning = true;

	//Ladataan tekstuuri..
	Texture texture;
	texture.readFromFile("textures/nhaikou.png");

	//Ladataan shaderit..
	Effect effect;
	effect.LoadShader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");

	//Päälooppi
	while (isRunning)
	{	
		//Tarkistaa onko jo piirretty kolmiota, jos ei niin piirretään
		if (isDrawn == false)
		{			
			std::cout << "Piirretään.." << std::endl;
			draw();	
		}



		//Ikkunan koon muuttamista varten olevaa koodia
		//Toistaiseksi turhaa, voi ignorata.

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glPopMatrix();
		//glMatrixMode(GL_PROJECTION);
		//glPopMatrix();
		//glMatrixMode(GL_MODELVIEW);
		//glPopMatrix();
		///////////////////////////////////////////////////////////////////////



		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
		}
	}
}

//Kolmion piirto
void Engine::draw()
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);


	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0);

	glEnd();

	std::cout << "Kolmio piirretty!" << std::endl;

	isDrawn = true;

	SDL_GL_SwapWindow(window);
}