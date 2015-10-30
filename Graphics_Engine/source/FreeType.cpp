//Laatija: Juuso Martikainen
//
//#include "FreeType.h"
//
//
//
//inline int nextP2(int a)
//{
//	int rval = 1;
//
//	while (rval < a) rval <<= 1;
//	return rval;
//}
//
//void makeDList(FT_Face face, char ch, GLuint baseList, GLuint * textBase)
//{
//	if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
//		throw std::runtime_error("FT_Load_Glyph failed");
//
//	FT_Glyph glyph;
//	if (FT_Get_Glyph(face->glyph, &glyph))
//		throw std::runtime_error("FT_Get_Glyph failed");
//
//	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
//	FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;
//
//	FT_Bitmap& bitmap = bitmapGlyph->bitmap;
//
//
//
//	int width = nextP2(bitmap.width);
//	int height = nextP2(bitmap.rows);
//
//	//Muistia textuuri datalle
//	GLubyte* expanded_data = new GLubyte[2 * width * height];
//
//	for (int i = 0; i < height; i++)
//	{
//		for (int j = 0; j < width;j++)
//		{
//			expanded_data[2 * (j + i*width)] = expanded_data[2 * (j + i * width) + 1] =
//				(i >= bitmap.width || j >= bitmap.rows) ?
//				0 : bitmap.buffer[j + bitmap.width*i];
//		}
//	}
//
//	glBindTexture(GL_TEXTURE_2D, textBase[ch]);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
//
//	delete[] expanded_data;
//
//	glNewList(baseList + ch, GL_COMPILE);
//
//	glBindTexture(GL_TEXTURE_2D, textBase[ch]);
//
//	glPushMatrix();
//
//	glTranslatef(bitmapGlyph->left, 0, 0);
//
//	glTranslatef(0, bitmapGlyph->top - bitmap.rows, 0);
//
//
//	float x = (float)bitmap.width / (float)width, y = (float)bitmap.rows / (float)height;
//
//
//	glBegin(GL_QUADS);
//	glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
//	glTexCoord2d(0, y); glVertex2f(0, 0);
//	glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
//	glTexCoord2d(x, 0);	glVertex2f(bitmap.width, bitmap.rows);
//	glEnd();
//	glPopMatrix();
//	glTranslatef(face->glyph->advance.x >> 6, 0, 0);
//
//	glEndList();
//
//}
//
//void fontData::init(const char * fname, unsigned int Height)
//{
//	textures = new GLuint[128];
//
//	this->Height = Height;
//
//	FT_Library library;
//	if (FT_Init_FreeType(&library))
//		throw std::runtime_error("FT_Init_Freetype failed");
//
//
//	FT_Face face;
//
//	if (FT_New_Face(library, fname, 0, &face))
//		throw std::runtime_error("FT_New_Face failed (probaply problems whit font file!");
//
//	FT_Set_Char_size(face, Height << 6, Height << 6, 96, 96);
//
//
//	listBase = glGenLists(128);
//	glGenTextures(128, textures);
//
//	for (unsigned char i = 0; i < 128; i++)
//		makeDList(face, i, listBase, textures);
//
//	FT_Done_Face(face);
//
//	FT_Done_Freetype(library);
//}
//
//void fontData::clean()
//{
//	glDeleteLists(listBase, 128);
//	glDeleteTextures(128, textures);
//	delete[] textures;
//}