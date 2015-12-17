// Laatija: Ville Koskinen //

#ifndef EFFECT_H
#define EFFECT_H

#include "Engine.h"



class Effect
{
public:	
	
	// Linkittää programin
	GLuint getProgram();

	//Lataa shaderin
	GLuint LoadShader(const char *vertex_path, const char *fragment_path);

private:
	//Lataa tekstuurin
	void load(std::string);		
	//Tarkistaa onko tekstuuri ladattu
	bool isLoaded();

	GLuint program;
};
#endif