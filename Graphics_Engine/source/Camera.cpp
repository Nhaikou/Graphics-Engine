// Laatija: Ville Koskinen

#include "Camera.h"


Camera::Camera()
	: position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, -1.0f)
{

}

void Camera::initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(position.x, position.y, position.z);
	glm::lookAt(glm::vec3(0.0f, 6000.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}