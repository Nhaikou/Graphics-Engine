// Laatija: Niko Kinnunen

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Engine.h"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(GLuint id, size_t w, size_t h);
	
	const GLuint& getId() const;

	int getWidth();
	int getHeight();

	bool readFromFile(const std::string& assetPath);

private:
	size_t width, height;
	GLuint id;
};
#endif;
