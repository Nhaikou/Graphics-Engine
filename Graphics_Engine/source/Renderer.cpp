// Laatija: Niko Kinnunen

#include "Renderer.h"
#include "Camera.h"
#include "FreeType.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define ScreenWidth 1280
#define ScreenHeight 720

Camera camera;
fontData font;
Renderer::Renderer()
	: vertexBufferPosition(0), projection(glm::ortho(0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight), 0.f, -1.f, 1.f))
{
	effect.LoadShader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");
}

void Renderer::render()
{
	camera.initialize();

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -1.0f);
	//font.init("Fontit/Arcon-regular.otf", 16);
	//glRasterPos2f(-0.40f, 0.35f);
	//font.print(font, 320, 200, "Active Freetype Text -%7.2f", 3);

	// piirr�, tunge vertexit jne
	for (Sprite* sprite : sprites) 
	{
		VertexPositionColorTexture vertices[4];
		vertices[0] = VertexPositionColorTexture{
			sprite->getPosition(),
			sprite->getColor(),
			glm::vec2(0, 1)
		};

		vertices[1] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth() * sprite->getScale().x, 0),
			sprite->getColor(),
			glm::vec2(1, 1)
		};

		vertices[2] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(0, sprite->getTexture()->getHeight() * sprite->getScale().y),
			sprite->getColor(),
			glm::vec2(0, 0)
		};

		vertices[3] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth() * sprite->getScale().x, sprite->getTexture()->getHeight() * sprite->getScale().y),
			sprite->getColor(),
			glm::vec2(1, 0)
		};

		glBufferSubData(
			GL_ARRAY_BUFFER,
			sizeof(VertexPositionColorTexture) * verticesPerSprite * vertexBufferPosition,
			sizeof(vertices),
			vertices
			);
		// liikuta "pointteria" eteenp�in
		vertexBufferPosition++;
	}

	glUseProgram(effect.getProgram());

	// bindaa shaderi
	for (size_t i = 0; i < sprites.size(); i++) {
		Sprite* sprite = sprites[i];
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getId());
		//assert(glGetError() == 0);

		GLuint matrixLocation = glGetUniformLocation(effect.getProgram(), "MVP");
		//assert(glGetError() == 0);

		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawElements(
			GL_TRIANGLES,
			indicesPerSprite,
			GL_UNSIGNED_INT,
			(void*)(indicesPerSprite * i * sizeof(unsigned int))
			);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// unbindaus
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vertexBufferPosition = 0;
}

void Renderer::init()
{
	createIndexBuffer();

	createVertexBuffer();
}

void Renderer::createIndexBuffer()
{
	indices.reserve(indicesPerSprite * initialBufferSize);

	for (unsigned int i = 0; i < initialBufferSize * indicesPerSprite; i += verticesPerSprite)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * indices.size(), // indeksien koko tavuina
		indices.data(),
		GL_STATIC_DRAW
		);
	
	// poistetaan bufferi k�yt�st�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::createVertexBuffer()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorTexture)
		* initialBufferSize * 4, nullptr, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));

	// poistetaan bufferi k�yt�st�
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Renderer::add(Sprite* sprite)
{
	sprites.push_back(sprite);
}

void Renderer::remove(Sprite*)
{

}

Renderer::~Renderer()
{

}