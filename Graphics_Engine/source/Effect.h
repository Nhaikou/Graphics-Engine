// Laatija: Ville Koskinen //

#ifndef EFFECT_H
#define EFFECT_H

#include "Engine.h"
#define ESZ(elem) (int)elem.size()


class Effect
{
public:
	// P‰‰konstruktori
	Effect();

	// Lataa shaderin ja tuhoaa sen
	bool loadShader(std::string sFile, int a_iType);
	void deleteShader();

	// Tarkistaa onko shaderi ladattu
	bool isLoaded();

	// Nappaa shaderin ID:n
	unsigned int getShaderID();


private:
	unsigned int uiShader;	// Shaderin ID
	int iType;				// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded;			// Tarkistaa onko shaderi ladattu ja kompilattu
};


class EffectProgram
{
public:
	// P‰‰konstruktori
	EffectProgram();

	// Luo ja tuhoaa programin
	void createProgram();
	void deleteProgram();

	// Lis‰‰ shaderin
	bool addShader(Effect* shShader);

	// Linkitt‰‰ programin
	bool linkProgram();

	// Use program. Mit‰h‰n se voisi tehd‰. Osaatko arvata?
	void useProgram();

	// Nappaa programin ID:n
	unsigned int getProgramID();
	

protected:
	unsigned int uiProgram;	// Program ID
	bool bLinked;			// Onko program linkitetty?
};


#endif