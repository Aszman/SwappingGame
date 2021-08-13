#include "tile.h"


Tile::Tile(size_t _realID,  size_t _expectedID, size_t _size)
{
	set(_realID, _expectedID, _size);
}

Tile::Tile(const Tile & other)
{
	this->copy(other);
}

Tile& Tile::operator=(const Tile & other)
{
	if (this != &other)
	{
		this->terminate();
		this->copy(other);
	}
	return *this;
}

Tile::~Tile()
{
	this->terminate();
}

void Tile::draw()const
{
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Tile::set(size_t _realID, size_t _expectedID, size_t _size)
{
	this->realID = _realID;
	this->expectedID = _expectedID;
	this->size = _size;

	float tileWidth = 1 / float(size);
	float tileHeight = 1 / float(size);

	setTileCoords(tileWidth, tileHeight);
	setTextCoords(tileWidth, tileHeight);
	genBuffers();
	setBuffers();

}

void Tile::setTileCoords(float & tileWidth, float & tileHeight)
{
	float xTile, yTile;
	xTile = (realID % size) * tileWidth;
	yTile = (realID / size + 1) * tileHeight;
	
	//setting Tile positions
	this->coords[0] = this->coords[5] = xTile;
	this->coords[1] = this->coords[16] = 1 - yTile;
	this->coords[10] = this->coords[15] = xTile + tileWidth;
	this->coords[6] = this->coords[11] = 1 - yTile + tileHeight;
	this->coords[2] = this->coords[7] = this->coords[12] = this->coords[17] = 0;
}

void Tile::setTextCoords(float & tileWidth, float & tileHeight)
{
	float xTex, yTex;
	xTex = (expectedID % size) * tileWidth;
	yTex = (expectedID / size + 1) * tileHeight;

	//setting Texture positions
	this->coords[3] = this->coords[8] = xTex;
	this->coords[4] = this->coords[19] = 1- yTex;
	this->coords[13] = this->coords[18] = xTex + tileWidth;
	this->coords[9] = this->coords[14] = 1 - yTex + tileHeight;
}

void Tile::genBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Tile::setBuffers()
{
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), this->coords, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Tile::copy(const Tile & other)
{
	this->realID = other.realID;
	this->expectedID = other.expectedID;
	this->size = other.size;


	for (int i = 0; i < 20; ++i)
	{
		this->coords[i] = other.coords[i];
	}

	this->genBuffers();
	this->setBuffers();
}

void Tile::terminate()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}