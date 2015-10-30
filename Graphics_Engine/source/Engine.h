// Laatija: Niko Kinnunen
#ifndef ENGINE_H
#define ENGINE_H
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

class Engine
{
public:
	Engine();
	~Engine();

	// estet‰‰n asettaminen ja kopiointi
	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;


	//k‰ynnist‰‰ moottorin
	void run();

	// Alustetaan SDL ja OpenGL
	void initialize(int Window_Width, int Window_Height);
	
private:
	SDL_Window* window;
	SDL_GLContext context;

	bool isRunning;

	int Window_Width;
	int Window_Height;
};
#endif;