//// Laatija: Ville Koskinen //
//
//#ifndef EFFECT_H
//#define EFFECT_H
//
//#include "Engine.h"
//#define ESZ(elem) (int)elem.size()
//
//
//class Effect
//{
//public:
//	// P‰‰konstruktori
//	Effect();
//
//	// Lataa shaderin ja tuhoaa sen
//	bool loadShader(std::string sFile, int a_iType);
//	void deleteShader();
//
//	// Tarkistaa onko shaderi ladattu
//	bool isLoaded();
//
//	// Nappaa shaderin ID:n
//	unsigned int getShaderID();
//
//
//private:
//	unsigned int uiShader;	// Shaderin ID
//	int iType;				// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
//	bool bLoaded;			// Tarkistaa onko shaderi ladattu ja kompilattu
//};
//
//
//class EffectProgram
//{
//public:
//	// P‰‰konstruktori
//	EffectProgram();
//
//	// Luo ja tuhoaa programin
//	void createProgram();
//	void deleteProgram();
//
//	// Lis‰‰ shaderin
//	bool addShader(Effect* shShader);
//
//	// Linkitt‰‰ programin
//	bool linkProgram();
//
//	// Use program. Mit‰h‰n se voisi tehd‰. Osaatko arvata?
//	void useProgram();
//
//	// Nappaa programin ID:n
//	unsigned int getProgramID();
//	
//
//protected:
//	unsigned int uiProgram;	// Program ID
//	bool bLinked;			// Onko program linkitetty?
//};
//

//Vanhaa koodia, ignoraa

//static struct
//{
//	GLuint vertex_shader, fragment_shader, program;
//
//	struct
//	{
//		GLint fade_factor;
//		GLint textures[2];
//	} uniforms;
//
//	struct
//	{
//		GLint position;
//	} attributes;
//
//	GLfloat fade_factor;
//} g_resources;
//
//static GLuint make_shader(GLenum type, const char *filename)
//{
//	GLint length;
//	char *source = file_content(filename, &length);
//	GLuint shader;
//	GLint shader_OK;
//
//	if (!source)
//	{
//		return 0;
//	}
//
//	shader = glCreateShader(type);
//	glShaderSource(shader, 1, (const GLchar**)&source, &length);
//	free(source);
//	glCompileShader(shader);
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_OK);
//	
//	if (!shader_OK)
//	{
//		std::cout << stderr << " Failed to compile " << filename << "!" << std::endl;	
//		//show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
//		glDeleteShader(shader);
//		return 0;
//	}	
//}
//
//static GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
//{
//	GLint program_OK;
//
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vertex_shader);
//	glAttachShader(program, fragment_shader);
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &program_OK);
//
//	if (!program_OK)
//	{
//		std::cout << stderr << " Failed to link shader program!" << std::endl;
//		//show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
//		glDeleteProgram(program);
//		return 0;
//	}
//	return program;
//}
//
//static int make_resources(void)
//{
//	g_resources.vertex_shader = make_shader(
//		GL_VERTEX_SHADER,
//		"testi"
//		);
//	if (g_resources.vertex_shader == 0)
//	{
//		return 0;
//	}
//
//	g_resources.fragment_shader = make_shader(
//		GL_FRAGMENT_SHADER,
//		"testi"
//		);
//	if (g_resources.fragment_shader == 0)
//	{
//		return 0;
//	}
//
//	g_resources.program = make_program(
//		g_resources.vertex_shader,
//		g_resources.fragment_shader
//		);
//	if (g_resources.program == 0)
//	{
//		return 0;
//	}
//
//	g_resources.uniforms.fade_factor
//		= glGetUniformLocations(g_resources_program, "fade_factor");
//	g_resources
//
//}
//#endif