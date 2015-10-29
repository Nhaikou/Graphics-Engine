// Laatija: Niko Kinnunen

#include "Sprite.h"

Sprite::Sprite(const Texture* texture)
	: texture(texture)
{

}

glm::vec2 Sprite::getPosition()
{
	return position;
}

glm::vec2 Sprite::getScale()
{
	return scale;
}

float Sprite::getRotation()
{
	return rotation;
}

glm::vec4 Sprite::getColor()
{
	return color;
}

void Sprite::setPosition(glm::vec2 pos)
{
	this->position*(pos);
}

void Sprite::setScale(glm::vec2 scale)
{
	this->scale*(scale);
}

void Sprite::setRotation(float rot)
{
	this->rotation*(rot);
}

void Sprite::setColor(glm::vec4 color)
{
	this->color*(color);
}

Sprite::~Sprite()
{
	// muistivuotojen korjaaminen
}