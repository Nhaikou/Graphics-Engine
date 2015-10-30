//// Laatija: Ville Koskinen //
//
//#include "Effect.h"
//
//
//Effect::Effect()
//{
//	bLoaded = false;
//}
//
//bool Effect::loadShader(std::string sFile, int a_iType)
//{
//	FILE* fp = fopen(sFile.c_str(), "rt");
//	if (!fp)return false;
//
//
//	std::vector<std::string> sLines;
//	char sLine[255];
//	while (fgets(sLine, 255, fp))sLines.push_back(sLine);
//	fclose(fp);
//
//	const char** sProgram = new const char*[ESZ(sLines)];
//	for (int i , ESZ(sLines))sProgram[i] = sLines[i].c_str();
//
//	uiShader = glCreateShader(a_iType);
//
//	glShaderSource(uiShader, ESZ(sLines), sProgram, NULL);
//	glCompileShader(uiShader);
//
//	delete[] sProgram;
//
//	int iCompilationStatus;
//	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);
//
//	if (iCompilationStatus == GL_FALSE)return false;
//	iType = a_iType;
//	bLoaded = true;
//
//	return 1;
//}
//
//bool Effect::isLoaded()
//{
//	return bLoaded;
//}
//
//unsigned int Effect::getShaderID()
//{
//	return uiShader;
//}
//
//void Effect::deleteShader()
//{
//	if (!isLoaded()) return;
//	bLoaded = false;
//	glDeleteShader(uiShader);
//}
//
//
//
//EffectProgram::EffectProgram()
//{
//	bLinked = false;
//}
//
//void EffectProgram::createProgram()
//{
//	uiProgram = glCreateProgram();
//}
//
//bool EffectProgram