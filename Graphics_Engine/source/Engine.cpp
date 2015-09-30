// Laatija: Niko Kinnunen
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
		// Tyhjää ikkunan
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		//Laatija: Ville Koskinen//

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Kolmion vektorit
		static const GLfloat g_vertex_buffer_data[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		// Kääntää määritettyä akselia 30ms jälkeen
		SDL_Delay(30);
		// Akselin kääntökulma
		float _angle = 2.0f;
		// Käännettävä akseli ( X, Y, Z )
		glRotatef(_angle, 0.0f, 0.0f, 0.5f);

		// Tunnistaa / nimeää vertexbufferin
		GLuint vertexBuffer;
		// Tekee yhden bufferin
		glGenBuffers(1, &vertexBuffer);
		// Seuraava komento "tajuaa" että puhutaan bufferista
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// Antaa vertices OpenGL:lle
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		// Attribuuttibufferi
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,			// attribuutti 0
			3,			// koko
			GL_FLOAT,	// tyyppi
			GL_FALSE,	// normalisoitu?
			0,			// stride
			(void*)0	// array buffer offsetti
			);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		SDL_Delay(30);
		glClear(GL_ARRAY_BUFFER);
		///////////////////////////////

		

		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

	}
}