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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ikkunan taustan v‰ri

	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	//std::cout << "OpenGL context version: " << versionMajor << ", " << versionMinor << std::endl;

	std::cout << std::endl;
	

	std::cout << "\n\n-------------------------------------------\n\nCONTROLS:\n\n - Arrow keys to move\n - Numpad 8 & 2 to scale\n - Numpad 4 & 6 to rotate\n\n-------------------------------------------\n\n" << std::endl;
}

//Tarvitaan p‰‰loopissa komennettavan spriten vaihtoon
int selectedSprite = 1;

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
	//texture2.readFromFile("textures/lich_king.png");
	texture3.readFromFile("textures/kikki.png");
	texture4.readFromFile("textures/black.png");
	
	Renderer renderer;
	renderer.init();
	Sprite* s = new Sprite(&texture);
	Sprite* s2 = new Sprite(&texture2);
	Sprite* s3 = new Sprite(&texture3);
	Sprite* s4 = new Sprite(&texture3);
	Sprite* s5 = new Sprite(&texture4);


	//s->setColor(glm::vec4(0, 0, 1, 0));
	s2->setScale(glm::vec2(1.5, 1.5));

	s3->setPosition(glm::vec2(1280 - 202.0f, 720 - 217.0f));
	s3->setScale(glm::vec2(1, 1));

	s4->setPosition(glm::vec2(205, 720 - 08.0f));
	s4->setScale(glm::vec2(-1, -1));

	s5->setColor(glm::vec4(1, 0.5, 0, 1));
	s5->setPosition(glm::vec2(1280 / 2 - 100, 200));

	renderer.add(s5);
	renderer.add(s);
	//renderer.add(s2);
	renderer.add(s3);
	renderer.add(s4);
	

	

	//P‰‰looppi
	while (isRunning)
	{	
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


		// sprite 3 "Kikkihiiri kuvat"
		s3->setRotation(s3->getRotation() + 2.0f);
		s4->setRotation(s4->getRotation() - 2.0f);

		// sprite 4 "Neliˆ"
		s5->setRotation(s5->getRotation() + 0.2f);
		

		//Tarkkailee tekeekˆ k‰ytt‰j‰ jotain
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			//Nappia painetaan n‰pp‰imistˆll‰..
			case SDL_KEYDOWN:

				//Mit‰ nappia painettiin?
				switch (event.key.keysym.sym)
				{
				//Meepo liikkuu oikealle
				case SDLK_RIGHT:
					s->setPosition(s->getPosition() + glm::vec2(10.0f, 0.0f));
					break;

				//Meepo liikkuu vasemmalle
				case SDLK_LEFT:
					s->setPosition(s->getPosition() + glm::vec2(-10.0f, 0.0f));
					break;

				//Meepo liikkuu ylˆs
				case SDLK_UP:
					s->setPosition(s->getPosition() + glm::vec2(0.0f, -8.0f));
					break;

				//Meepo liikkuu alas
				case SDLK_DOWN:
					s->setPosition(s->getPosition() + glm::vec2(0.0f, 8.0f));
					break;

				//Meepo kasvaa isommaksi
				case SDLK_KP_8:
					s->setScale(s->getScale() + glm::vec2(0.05f, 0.05f));
					break;
					
				//Meepo kutistuu pienemm‰ksi
				case SDLK_KP_2:
					s->setScale(s->getScale() + glm::vec2(-0.05f, -0.05f));
					break;

				//Meepo k‰‰ntyy myˆt‰p‰iv‰‰n
				case SDLK_KP_6:
					s->setRotation(s->getRotation() + 3.5f);
					break;

				//Meepo k‰‰ntyy vastap‰iv‰‰n
				case SDLK_KP_4:
					s->setRotation(s->getRotation() - 3.5f);
					break;

				//Ohjelma lopetetaan
				case SDLK_ESCAPE:
					SDL_QUIT;
					SDL_DestroyWindow(window);
					isRunning = false;
				}
			//Napista p‰‰stettiin irti
			case SDL_KEYUP:
				break;
			}
		}

		renderer.render();
		SDL_GL_SwapWindow(window);
	}
}