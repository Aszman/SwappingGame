#include "tile.h"
#include <iostream>

Tile::Tile(unsigned int _realID, unsigned int _expectedID) :realID(_realID), expectedID(_expectedID)
{
	float tileWidth = 1 / float(size);
	float tileHeight = 1 / float(size);
	setTileCoords(tileWidth, tileHeight);
	setTextCoords( tileWidth, tileHeight);
	setBuffers();
}

void Tile::setTileCoords(float & tileWidth, float & tileHeight)
{
	float xTile, yTile;
	xTile = (realID % size) * tileWidth;
	yTile = (realID / size) * tileHeight;
	
	//setting Tile positions
	this->coords[0] = this->coords[5] = xTile;
	this->coords[1] = this->coords[16] = yTile;
	this->coords[10] = this->coords[15] = xTile + tileWidth;
	this->coords[6] = this->coords[11] = yTile + tileHeight;
	this->coords[2] = this->coords[7] = this->coords[12] = this->coords[17] = 0;
}

void Tile::setTextCoords(float &tileWidth, float &tileHeight)
{
	float xTex, yTex;
	xTex = (expectedID % size) * tileWidth;
	yTex = (expectedID / size) * tileHeight;

	//setting Texture positions
	this->coords[3] = this->coords[8] = xTex;
	this->coords[4] = this->coords[19] = yTex;
	this->coords[13] = this->coords[18] = xTex + tileWidth;
	this->coords[9] = this->coords[14] = yTex + tileHeight;
}

void Tile::setBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), this->coords, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Tile::draw()const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Tile::~Tile()
{
	this->terminate();
}

void Tile::terminate()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}