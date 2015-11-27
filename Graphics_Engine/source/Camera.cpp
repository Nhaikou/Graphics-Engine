// Laatija: Ville Koskinen

#include "Camera.h"
#define ScreenWidth 1280
#define ScreenHeight 720

Camera::Camera()
{
}

enum ViewPortMode
{
	VIEWPORT_MODE_FULL,
	VIEWPORT_MODE_HALF_CENTER,
	VIEWPORT_MODE_HALF_TOP,
	VIEWPORT_MODE_QUAD,
	VIEWPORT_MODE_RADAR
};

int gViewportMode = VIEWPORT_MODE_FULL;

bool Camera::initialize()
{
	//Set the viewport
	glViewport(0.f, 0.f, ScreenWidth, ScreenHeight);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, ScreenWidth, ScreenHeight, 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return true;
}

void Camera::render()
{
	glLoadIdentity();
	glTranslatef(ScreenWidth / 2.0f, ScreenHeight / 2.0f, 0.0f);

	if (gViewportMode == VIEWPORT_MODE_FULL)
	{
		glViewport(5.0f, 1.0f, ScreenWidth, ScreenHeight);
	}
	else if (gViewportMode == VIEWPORT_MODE_HALF_CENTER)
	{
		glViewport(ScreenWidth / 4.0f, ScreenHeight / 4.0f, ScreenWidth / 2.0f, ScreenHeight / 2.0f);
	}
	else if (gViewportMode == VIEWPORT_MODE_HALF_TOP)
	{
		glViewport(ScreenWidth / 4.0f, ScreenHeight / 2.0f, ScreenWidth / 2.0f, ScreenHeight / 2.0f);
	}
}