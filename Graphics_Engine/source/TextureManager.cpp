// Laatija: Niko Kinnunen
#include "TextureManager.h"

TextureManager::TextureManager()
{

}

Texture* TextureManager::load(std::string assetPath)
{
	if (isLoaded(assetPath))
	{
		return nullptr;
	}
	return nullptr;
}

bool TextureManager::isLoaded(std::string& texture) const
{
	return textures.find(texture) != textures.end();
}

void TextureManager::unLoad(const std::string& texture)
{

}

void TextureManager::unLoadEverything()
{

}

TextureManager::~TextureManager()
{

}