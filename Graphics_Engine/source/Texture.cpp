// Laatija: Niko Kinnunen
#include "Texture.h"
#include "LodePNG\lodepng.h"

Texture::Texture() : width(0), height(0)
{

}

Texture::Texture(size_t w, size_t h) : id(0), width(w), height(h)
{

}

// käytämme ainoastaan .PNG tiedostoja kuvien lataamiseen
bool Texture::readFromFile(const std::string& path)
{
	std::vector<unsigned char> png, pixels;

	lodepng::load_file(png, path);


	size_t error = lodepng::decode(pixels, width, height, png.data(), png.size());
	
	// jos tiedostoa ei löydy
	if (error)
	{
		std::cout << "Error loading texture file" << error << ": " << lodepng_error_text(error) << std::endl;
		return false;
	}

	// annetaan tekstuurille id
	glGenTextures(1, &id);

	// sidotaan tekstuuri muokattavaksi
	glBindTexture(GL_TEXTURE_2D, id);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());


	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	// pois sidotaan tekstuuri
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

const GLuint& Texture::getId() const
{
	return id;
}

Texture::~Texture()
{
	//tuhotaan tekstuuri
	glDeleteTextures(1, &id);
}