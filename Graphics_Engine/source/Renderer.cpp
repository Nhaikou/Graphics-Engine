// Laatija: Niko Kinnunen

#include "Renderer.h"


Renderer::Renderer()
{

}

void Renderer::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// piirrä, tunge vertexit jne
	for (Sprite* sprite : sprites) {


		VertexPositionColorTexture vertices[4];
		vertices[0] = VertexPositionColorTexture{
			sprite->getPosition(),
			sprite->getColor(),
			glm::vec2(0, 1)
		};

		vertices[1] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth(), 0),
			sprite->getColor(),
			glm::vec2(1, 1)
		};

		vertices[2] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(0, sprite->getTexture()->getHeight()),
			sprite->getColor(),
			glm::vec2(0, 0)
		};

		vertices[3] = VertexPositionColorTexture{
			sprite->getPosition() + glm::vec2(sprite->getTexture()->getWidth(), sprite->getTexture()->getHeight()),
			sprite->getColor(),
			glm::vec2(1, 0)
		};

		glBufferSubData(
			GL_ARRAY_BUFFER,
			sizeof(VertexPositionColorTexture) * verticesPerSprite * vertexBufferPosition,
			sizeof(vertices),
			vertices
			);
		// liikuta "pointteria" eteenpäin
		vertexBufferPosition++;
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

	for (unsigned short i = 0; i < initialBufferSize * indicesPerSprite; i++)
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

	// poistetaan bufferi käytöstä
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::createVertexBuffer()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorTexture)
		* initialBufferSize * 4, nullptr, GL_STREAM_DRAW);

	// poistetaan bufferi käytöstä
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