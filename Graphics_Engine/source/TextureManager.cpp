// Laatija: Niko Kinnunen
#include "TextureManager.h"

// Annetaan tekstuurien tiedostopolku
TextureManager::TextureManager(const std::string& fileRootDirectory = "../sample/Graphics_Demo/textures") : fileRoot(fileRootDirectory)
{
	// polkuerotin
	std::size_t index = fileRoot.rfind("\\", fileRoot.length() - 1);
	if (index != std::string::npos)
	{
		fileRoot.erase(index, 1);
	}
}

// Ladataan tekstuurit tiedostosta.
Texture* TextureManager::load(std::string assetPath)
{
	if (!isLoaded(assetPath))
	{
		std::string path = fileRoot + "\\" + assetPath;

		Texture* texture = new Texture();
		textures.insert(std::pair<std::string, Texture*>(assetPath, texture));

		if (!texture->readFromFile(path))
		{
			throw std::runtime_error("Can't open file " + path + "!");
		}

		return texture;
	}

	return textures[assetPath];
}

bool TextureManager::isLoaded(std::string& texture) const
{
	return textures.find(texture) != textures.end();
}

const std::string& TextureManager::getfileRoot() const
{
	return fileRoot;
}

void TextureManager::unLoad(const std::string& texture)
{
	
}

void TextureManager::unLoadEverything()
{
	// tuhotaan kaikki textuurit
	textures.clear();
}

TextureManager::~TextureManager()
{

}