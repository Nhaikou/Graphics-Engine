// Laatija: Ville Koskinen

#include "Camera.h"

const int ScreenWidth = 1280;
const int ScreenHeight = 720;
const int CameraWidth = 800;
const int CameraHeight = 600;

Camera::Camera()
{
}

//Tekee kameran
void Camera::initialize()
{
	camera = { 0, 0, CameraWidth, CameraHeight };
}

//Antaa kameralle koordinaatit ikkunaan nähden
void Camera::render()
{
	camera.x = 0;
	camera.y = 0;
}