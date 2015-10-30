// Laatija: Niko Kinnunen

#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "glm\glm.hpp"

class Sprite
{
public:
	Sprite(const Texture* texture);
	~Sprite();

	glm::vec2 getPosition();
	glm::vec2 getScale();

	float getRotation();

	glm::vec4 getColor();

	void setPosition(glm::vec2 pos);
	void setScale(glm::vec2 scale);
	void setRotation(float rot);
	void setColor(glm::vec4 color);

private:

	const Texture* texture;
	
	glm::vec2 position;
	glm::vec2 scale;
	
	float rotation;

	glm::vec4 color;

};
#endif;