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

	const Texture* getTexture() const
	{
		return texture;
	}

private:

	const Texture* texture;
	
	glm::vec2 position;
	glm::vec2 scale = { 1.0, 1.0 };
	
	float rotation = 0;

	glm::vec4 color;

};
#endif;