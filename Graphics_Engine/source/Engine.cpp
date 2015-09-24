#include "Engine.h"
#include <cassert>
#include <Windows.h>

Engine::Engine() : running(false), window(nullptr), Window_Width(0), Window_Height(0)
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
	glGetIntegerv(GL_MAJOR_VERSION, &versionMinor);
	std::cout << "OpenGL context version: " << versionMajor << ", " << versionMinor << std::endl;


}

void Engine::run()
{
	initialize();
	SDL_Event event;
	running = true;
	
	while (running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

	}
}