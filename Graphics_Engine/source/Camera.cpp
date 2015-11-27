// Laatija: Ville Koskinen

#include "Camera.h"
#include "GLFW\glfw3.h"


Camera::Camera()
{
}

void Camera::initialize()
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::normalize(position - target);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, direction));

	glm::vec3 camUp = glm::cross(direction, right);

	GLfloat radius = 10.0f;
	GLfloat camX = sin(glfwGetTime()) * radius;
	GLfloat camZ = cos(glfwGetTime()) * radius;

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), 
					   glm::vec3(0.0f, 0.0f, 0.0f), 
					   glm::vec3(0.0f, 1.0f, 0.0f));
}