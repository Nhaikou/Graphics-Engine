////Laatija: Juuso Martikainen

#include "FreeType.h"


	inline int nextP2(int a)
	{
		int rval = 1;

		while (rval < a) rval <<= 1;
		return rval;
	}


	//Tehd‰‰n lista jolle haetaan oikeat kirjaimet
	void makeDList(FT_Face face, char ch, GLuint baseList, GLuint * textBase)
	{
		//Freetype muuttaa kirjaimet bitmap muotoon
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
			throw std::runtime_error("FT_Load_Glyph failed");
		//Siirret‰‰n Face Glyph Glyph objektiin
		FT_Glyph glyph;
		if (FT_Get_Glyph(face->glyph, &glyph))
			throw std::runtime_error("FT_Get_Glyph failed");
		//Glyphist‰ bitmapiksi
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

		//Helpotetaan bitmapin k‰yttˆ‰
		FT_Bitmap& bitmap = bitmapGlyph->bitmap;


		//Fucktio joka auttaa hakemaan koot bitmapin tiedoista, joita tarvitsemme tekstuurin luomiseen
		int width = nextP2(bitmap.width);
		int height = nextP2(bitmap.rows);

		//Muistia textuuri datalle
		GLubyte* expanded_data = new GLubyte[2 * width * height];

		//T‰yt‰mme dataa laajennettuun bitmappiin
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				expanded_data[2 * (j + i*width)] = expanded_data[2 * (j + i * width) + 1] =
					(i >= bitmap.width || j >= bitmap.rows) ?
					0 : bitmap.buffer[j + bitmap.width*i];
			}
		}
		//Tekstuuri Parametrej‰
		glBindTexture(GL_TEXTURE_2D, textBase[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//Tekstuurin luonti
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
		//Tekstuuri valmis, emme en‰‰ tarvitse laajennettua dataa
		delete[] expanded_data;

		//Teemme display listan
		glNewList(baseList + ch, GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, textBase[ch]);

		glPushMatrix();

		//Kirjainten v‰lit
		glTranslatef(bitmapGlyph->left, 0, 0);

		//'g' ja'y' tapaukset
		glTranslatef(0, bitmapGlyph->top - bitmap.rows, 0);

		//Poistetaan turha tyhj‰tila kirjainten sis‰lt‰
		float x = (float)bitmap.width / (float)width, y = (float)bitmap.rows / (float)height;

		//Piirt‰‰  tekstuurikartta Quads. Freetypen bitmap ei laita asioita kuten haluamme mutta linkattuna quadsiin, tulokset ovat haluttuja.
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
		glTexCoord2d(x, 0);	glVertex2f(bitmap.width, bitmap.rows);
		glEnd();
		glPopMatrix();
		glTranslatef(face->glyph->advance.x >> 6, 0, 0);




		//lopetamme Display listan
		glEndList();

	}

	void fontData::init(const char * fname, unsigned int Height)
	{
		//Allokoidaan v‰h‰n muistia varastoimaan tekstuuri id:t‰
		textures = new GLuint[128];

		this->Height = Height;

		//Luo ja k‰ytt‰‰ freetype fontti kirjastoa
		FT_Library library;
		if (FT_Init_FreeType(&library))
			throw std::runtime_error("FT_Init_Freetype failed");

		//Freetypen objekti joka pit‰‰ sis‰ll‰‰n fonttin tiedot
		FT_Face face;


		//Lataa fonttin tiedot tiedostosta, jos koodi hajoaa niin se hajoaa t‰‰ll‰.
		if (FT_New_Face(library, fname, 0, &face))
			throw std::runtime_error("FT_New_Face failed (probaply problems whit font file!)");
		
		
		//Koska vitun freetype tulkitsee fontin kokoa koossa 1/64 pikselist‰, joudumme pyyt‰m‰‰n koot 64 kertaisina.
		//h << 6 on kaunisteltu muoto.
		FT_Set_Char_Size(face, Height << 6, Height << 6, 96, 96);
		

		//Kysyt‰‰n openGL:‰ allokoimaan resursseja tekstuureille ja Display listalle jotka aiomme tehd‰
		listBase = glGenLists(128);
		glGenTextures(128, textures);
		
		//Luo kaikki fontti Display listat
		for (unsigned char i = 0; i < 128; i++)
			makeDList(face, i, listBase, textures);


		//Naama informaatiota ei tarvita en‰‰ joten se vapautetaan.
		FT_Done_Face(face);

		//Sama fontti kirjastolle
		FT_Done_FreeType(library);
	}

	void fontData::clean()
	{
		glDeleteLists(listBase, 128);
		glDeleteTextures(128, textures);
		delete[] textures;
	}

	//Puskee projektio matriksin koordinaatit samoiksi kuin ikkunan koordinaatit
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

	//Poppaa projektio matrixin muuttamatta nykyist‰ matriksi moodia 
	inline void pop_projection_matrix()
	{
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void fontData::print(const fontData &ftFont, float x, float y, const char *fmt, ...)
	{
		//Et‰isyydet mitataan ikkunan pikseleiss‰
		pushScreenCoordinateMatrix();
		

		GLuint font = ftFont.listBase;
		//Teemme kokoa hieman isommaksi, j‰tt‰‰ hieman tilaa rivien v‰liin
		float h = ftFont.Height / .63f;
		char text[256];							//Pit‰‰ stringi‰
		va_list ap;								//Pointteri argumentteihin

		if (fmt == NULL)						//Jos ei ole teksti‰ niin sit‰ ei tarvitse tehd‰
			*text = 0;
		else
		{
			va_start(ap, fmt);					//Korjaa stringi‰ muuttujille
			vsprintf_s(text, fmt, ap);				//Ja k‰‰nt‰‰ symbolit numeroiksi
			va_end(ap);							//Tulokset s‰ilˆt‰‰n tekstiin
		}


		//Pilkkoo antamamme tekstin riveihin
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




		//Tekstin kirjoittaminen tapahtuu t‰‰ll‰, jokaiselle riville Modelview matriisi resetoidaan
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
