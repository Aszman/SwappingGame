#include "board.h"

Board::Board(size_t _size, const char* vertexPath, const char* fragmentPath) : size(_size), shader(vertexPath, fragmentPath)
{
	tiles = new Tile[size * size];
	for (int i = 0; i < size * size; ++i)
	{
		tiles[i].set(i, size * size - 1 - i, size);
	}

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f);

	this->shader.use();
	this->shader.setMat4("projection", projection);
	this->shader.setMat4("view", view);
	
}

Board::~Board()
{
	delete[] this->tiles;
}

void Board::draw()const
{
	this->shader.use();
	this->shader.setFloat("alpha", 1.0f);

	for (int i = 0; i < this->size * this->size - 1; ++i)
	{
		this->tiles[i].draw();
	}

	this->shader.setFloat("alpha", 0.0f);
	this->tiles[this->size * this->size - 1].draw();
}