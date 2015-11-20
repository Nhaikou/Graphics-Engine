// Laatija: Ville Koskinen

#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


class Camera
{
	glm::vec3 position;
	glm::vec3 rotation;

public:
	Camera();
	void initialize();
};
#endif