// Laatija: Niko Kinnunen

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Engine.h"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(GLuint, int, int);
	
	GLuint getId();

	int getWidth();
	int getHeight();

private:
	int width, height;
	GLuint id;
};
#endif;
