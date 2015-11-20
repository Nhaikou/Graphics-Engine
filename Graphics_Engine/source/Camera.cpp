// Laatija: Ville Koskinen

#include "Camera.h"


Camera::Camera()
	: direction(0.0f, 0.0f, -1.0f), 
	  upVector(0.0f, 1.0f, 0.0f)
{

}

const glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + direction, upVector);
}






//void Camera::setCamera()
//{
//	//Kameran paikka
//	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//
//	//Kameran suunta
//	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//	glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTarget);
//
//	//Kameran 'oikea' ja 'ylös' akseli
//	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDir));
//	glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);
//}
//
//void Camera::useCamera()
//{
//	glm::mat4 view;
//	view = glm::lookAt( glm::vec3(0.0f, 0.0f, 3.0f),
//						glm::vec3(0.0f, 0.0f, 0.0f),
//						glm::vec3(0.0f, 1.0f, 0.0f));
//}