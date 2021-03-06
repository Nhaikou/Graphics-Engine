// Laatija: Niko Kinnunen

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Engine.h"
#include "Texture.h"
#include <map>
#include <string>
class TextureManager
{
public:
	TextureManager(const std::string& fileRootDirectory);
	~TextureManager();
	
	const std::string& getfileRoot() const;

	Texture* load(std::string texture);

	void unLoad(const std::string& texture);
	void unLoadEverything();

private:
	std::string fileRoot;
	std::map<std::string, Texture*> textures;
	bool isLoaded(std::string& texture) const;
};
#endif;