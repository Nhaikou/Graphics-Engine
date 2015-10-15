// Laatija: Niko Kinnunen

#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "glm\glm.hpp"

class Sprite
{
public:
	Sprite();
	~Sprite();

	glm::vec2 getPosition();
	glm::vec2 getScale();

	float getRotatio();

	glm::vec4 getColor();

	void setPosition(glm::vec2);
	void setScale(glm::vec2);
	void setRotation(float);
	void setColor(glm::vec4);

private:

	const Texture* texture;
	
	glm::vec2 position;
	glm::vec2 scale;
	
	float rotation;

	glm::vec4 color;

};
#endif;