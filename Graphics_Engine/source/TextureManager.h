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
	TextureManager();
	~TextureManager();
	
	Texture* load(std::string textures);

	void unLoad(const std::string& textures);
	void unLoadEverything();

private:
	std::map<std::string, Texture*> textures;
	bool isLoaded(std::string& textures) const;
};
#endif;