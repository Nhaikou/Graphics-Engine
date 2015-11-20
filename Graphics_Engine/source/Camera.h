// Laatija: Ville Koskinen

#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\trigonometric.hpp"


class Camera
{
	glm::vec3 position;
	glm::vec3 direction;
	const glm::vec3 upVector;

public:
	Camera();
	const glm::mat4 getViewMatrix();
};
#endif