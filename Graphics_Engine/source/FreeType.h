////////Laatija: Juuso Martikainen
////
#ifndef FREE_TYPE_H
#define FREE_TYPE_H
//FreeType 
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype\ftglyph.h>
#include <freetype\ftoutln.h>
#include <freetype\fttrigon.h>

//openGl
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
//STL
#include <vector>
#include <string>

//Helpottaa muita jotka k�ytt�v�t koodia nappaamaan heitt�m�mme poikkeukset
#include <stdexcept>

class fontData
{
	float Height;
	GLuint * textures;
	GLuint listBase;
public:

//	Init functio luo fontin korkeudella Height tiedostosta fname.
//
	void init(const char *fname, unsigned int Height);
//Vapauttaa kaikki resurssit jotka ovat fonteissa
	void clean();

	void print(const fontData &ftFont, float x, float y, const char *fmt, ...);
};
#endif