//Laatija: Juuso Martikainen

#include "FreeType.h"


	inline int nextP2(int a)
	{
		int rval = 1;

		while (rval < a) rval <<= 1;
		return rval;
	}

	void makeDList(FT_Face face, char ch, GLuint baseList, GLuint * textBase)
	{
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
			throw std::runtime_error("FT_Load_Glyph failed");

		FT_Glyph glyph;
		if (FT_Get_Glyph(face->glyph, &glyph))
			throw std::runtime_error("FT_Get_Glyph failed");

		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap& bitmap = bitmapGlyph->bitmap;



		int width = nextP2(bitmap.width);
		int height = nextP2(bitmap.rows);

		//Muistia textuuri datalle
		GLubyte* expanded_data = new GLubyte[2 * width * height];

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				expanded_data[2 * (j + i*width)] = expanded_data[2 * (j + i * width) + 1] =
					(i >= bitmap.width || j >= bitmap.rows) ?
					0 : bitmap.buffer[j + bitmap.width*i];
			}
		}

		glBindTexture(GL_TEXTURE_2D, textBase[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

		delete[] expanded_data;

		glNewList(baseList + ch, GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, textBase[ch]);

		glPushMatrix();

		glTranslatef(bitmapGlyph->left, 0, 0);

		glTranslatef(0, bitmapGlyph->top - bitmap.rows, 0);


		float x = (float)bitmap.width / (float)width, y = (float)bitmap.rows / (float)height;


		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
		glTexCoord2d(x, 0);	glVertex2f(bitmap.width, bitmap.rows);
		glEnd();
		glPopMatrix();
		glTranslatef(face->glyph->advance.x >> 6, 0, 0);

		glEndList();

	}

	void fontData::init(const char * fname, unsigned int Height)
	{
		textures = new GLuint[128];

		this->Height = Height;

		FT_Library library;
		if (FT_Init_FreeType(&library))
			throw std::runtime_error("FT_Init_Freetype failed");


		FT_Face face;

		if (FT_New_Face(library, fname, 0, &face))
			throw std::runtime_error("FT_New_Face failed (probaply problems whit font file!");

		FT_Set_Char_Size(face, Height << 6, Height << 6, 96, 96);
		
		listBase = glGenLists(128);
		glGenTextures(128, textures);

		for (unsigned char i = 0; i < 128; i++)
			makeDList(face, i, listBase, textures);

		FT_Done_Face(face);

		
		FT_Done_FreeType(library);
	}

	void fontData::clean()
	{
		glDeleteLists(listBase, 128);
		glDeleteTextures(128, textures);
		delete[] textures;
	}


	inline void pushScreenCoordinateMatrix()
	{
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glPopAttrib();
	}

	inline void pop_projection_matrix()
	{
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void fontData::print(const fontData &ftFont, float x, float y, const char *fmt, ...)
	{
		pushScreenCoordinateMatrix();
		

		GLuint font = ftFont.listBase;

		float h = ftFont.Height / .63f;
		char text[256];
		va_list ap;

		if (fmt == NULL)						//Jos ei ole tekstiä niin sitä ei tarvitse tehdä
			*text = 0;
		else
		{
			va_start(ap, fmt);
			vsprintf(text, fmt, ap);
			va_end(ap);
		}

		const char *start_line = text;
		std::vector<std::string>lines;
		for (const char *c = text; *c; c++)
		{
			if (*c == '\n')
			{
				std::string line;
				for (const char *n = start_line; n < c; n++) line.append(1, *n);
				lines.push_back(line);
				start_line = c + 1;
			}

			if (start_line)
			{
				std::string line;
				for (const char *n = start_line; n < c; n++);
				lines.push_back(line);
			}
		}
		glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glListBase(font);


		float modelview_matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

		for (int i = 0; i < lines.size(); i++)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(x, y - h*i, 0);
			glMultMatrixf(modelview_matrix);

			glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());

			glPopMatrix();


		}
		glPopAttrib();

		pop_projection_matrix();

	}
