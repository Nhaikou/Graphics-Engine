// Laatija: Ville Koskinen //
#ifndef EFFECT_H
#define EFFECT_H

#include "Engine.h"

class Effect
{
public:
	Effect();
	~Effect();

	//Luo linkitett‰v‰n programmin
	GLuint program;

	//Linkitt‰‰ kyseisen programmin
	GLuint getProgram();

	//Lataa tekstuurin
	void load(std::string);
	
	//Tarkistaa onko tekstuuri ladattu
	bool isLoaded();
};

//static void show_info_log(
//	GLuint object,
//	PFNGLGETSHADERIVPROC glGet__iv,
//	PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
//{
//	GLint log_length;
//	char *log;
//
//	glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
//	log = malloc(log_length);
//	glGet__InfoLog(object, log_length, NULL, log);
//	std::cout << stderr << " / " << log << std::endl;
//	free(log);
//}

static struct
{
	GLuint vertex_shader, fragment_shader, program;

	struct
	{
		GLint fade_factor;
		GLint textures[2];
	} uniforms;

	struct
	{
		GLint position;
	} attributes;

	GLfloat fade_factor;
} g_resources;

static GLuint make_shader(GLenum type, const char *filename)
{
	GLint length;
	char *source = file_content(filename, &length);
	GLuint shader;
	GLint shader_OK;

	if (!source)
	{
		return 0;
	}

	shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar**)&source, &length);
	free(source);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_OK);
	
	if (!shader_OK)
	{
		std::cout << stderr << " Failed to compile " << filename << "!" << std::endl;	
		//show_info_log(shader, glGetShaderiv, glGetShaderInfoLog);
		glDeleteShader(shader);
		return 0;
	}	
}

static GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{
	GLint program_OK;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &program_OK);

	if (!program_OK)
	{
		std::cout << stderr << " Failed to link shader program!" << std::endl;
		//show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
		glDeleteProgram(program);
		return 0;
	}
	return program;
}

static int make_resources(void)
{
	g_resources.vertex_shader = make_shader(
		GL_VERTEX_SHADER,
		"testi"
		);
	if (g_resources.vertex_shader == 0)
	{
		return 0;
	}

	g_resources.fragment_shader = make_shader(
		GL_FRAGMENT_SHADER,
		"testi"
		);
	if (g_resources.fragment_shader == 0)
	{
		return 0;
	}

	g_resources.program = make_program(
		g_resources.vertex_shader,
		g_resources.fragment_shader
		);
	if (g_resources.program == 0)
	{
		return 0;
	}

	g_resources.uniforms.fade_factor
		= glGetUniformLocations(g_resources_program, "fade_factor");
	g_resources

}
#endif