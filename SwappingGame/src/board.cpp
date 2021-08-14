#include "board.h"

const char* vertexPath = "src/Shaders/vertexShader.vert";
const char* fragmentPath = "src/Shaders/fragmentShader.frag";

Board::Board(size_t _size) : size(_size), shader(vertexPath, fragmentPath), tileHeight(1 / float(size)), tileWidth(1 / float(size))
{
	setCoords();
	setBuffers();

	tiles = new Tile[this->size * this->size];

	for (size_t i = 0; i < size * size; ++i)
	{
		tiles[i].set(i, size * size - i - 1, size);
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

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Board::draw()const
{
	glBindVertexArray(this->VAO);

	this->shader.use();
	this->shader.setFloat("alpha", 1.0f);

	for (size_t i = 0; i < this->size * this->size - 1; ++i)
	{
		this->tiles[i].draw(this->shader);
	}

	this->shader.setFloat("alpha", 0.0f);

	this->tiles[this->size * this->size -1].draw(this->shader);
}

void Board::setCoords()
{
	//x
	this->tileData[0] = this->tileData[3] = 0.0f;
	this->tileData[6] = this->tileData[9] = this->tileWidth;

	//y
	this->tileData[1] = this->tileData[10] =  1 - this->tileHeight;
	this->tileData[4] = this->tileData[7] = 1.0f;

	//z
	this->tileData[2] =	this->tileData[5] = this->tileData[8] = this->tileData[11] = 0.0f;
}

void Board::setBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->tileData), this->tileData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}