// Laatija: Niko Kinnunen
#include "Engine.h"
#include "Effect.h"
#include <cassert>
#include <Windows.h>
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"

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
	glGetError();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// korjaa .PNG kuvien taustat oikein

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ikkunan taustan väri

	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	//std::cout << "OpenGL context version: " << versionMajor << ", " << versionMinor << std::endl;

	std::cout << std::endl;
	
}


void Engine::run()
{
	initialize();
	SDL_Event event;
	isRunning = true;

	Camera camera;
	camera.initialize();

	//Ladataan tekstuuri..
	Texture texture;
	Texture texture2;
	Texture texture3;
	Texture texture4;
	Texture texture5;
	texture.readFromFile("textures/meepo.png");
	texture2.readFromFile("textures/lich_king.png");
	texture3.readFromFile("textures/kikki.png");
	texture4.readFromFile("textures/black.png");
	texture5.readFromFile("textures/nhaikou3.png");
	Renderer renderer;
	renderer.init();
	Sprite* s = new Sprite(&texture);
	Sprite* s2 = new Sprite(&texture2);
	Sprite* s3 = new Sprite(&texture3);
	Sprite* s4 = new Sprite(&texture4);
	Sprite* s5 = new Sprite(&texture5);
	s5->setScale(glm::vec2(3, 3));
	s->setColor(glm::vec4(0, 0, 1, 0));
	s4->setColor(glm::vec4(1, 0, 1, 1));
	s2->setScale(glm::vec2(1.5, 1.5));
	s3->setPosition(glm::vec2(1280 - 202.0f, 720 - 217.0f));
	renderer.add(s);
	renderer.add(s2);
	renderer.add(s3);
	//renderer.add(s4);
	//renderer.add(s5);

	//Päälooppi
	while (isRunning)
	{	
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		s5->setPosition(s5->getPosition() + glm::vec2(0.1f, 0.0f));
		s->setPosition(s->getPosition()+glm::vec2(0.2f, 0.2f));
		s3->setRotation(s->getRotation() + 0.2f);
		
		renderer.render();
		camera.render();

		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
		}
		SDL_GL_SwapWindow(window);
	}

}