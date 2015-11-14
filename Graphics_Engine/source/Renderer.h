// Laatija: Niko Kinnunen

#ifndef RENDERER_H
#define RENDERER_H

#include "Sprite.h"
#include "Effect.h"
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

struct VertexPositionColorTexture {
	glm::vec2 position;	// texturen positio
	glm::vec4 color;	// texturen v‰ri
	glm::vec2 uv; // texturen coordinantti
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void add(Sprite*);
	void remove(Sprite*);

	void render();
	void init();
private:
	Effect effect;

	void createIndexBuffer();
	void createVertexBuffer();

	const int initialBufferSize = 2048; // mahdollisten spritejen m‰‰r‰
	const int verticesPerSprite = 4;	// pisteiden m‰‰r‰ spriteill‰
	const int indicesPerSprite = 6;

	int vertexBufferPosition;

	std::vector<Sprite*> sprites;

	glm::mat4 projection;

	GLuint vertexBuffer;
	GLuint indexBuffer;

	std::vector<unsigned int> indices;

};
#endif;