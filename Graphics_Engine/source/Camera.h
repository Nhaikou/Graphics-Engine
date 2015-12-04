// Laatija: Ville Koskinen

#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "GLFW\glfw3.h"

class Camera
{
public:
	Camera();
	void initialize();
	void render();

protected:
	SDL_Rect camera;
};
#endif