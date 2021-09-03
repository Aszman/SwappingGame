#include "tile.h"

//constructor
Tile::Tile(size_t _positionID,  size_t _textureID, size_t _rowSize)
{
	this->positionID = _positionID;
	this->textureID = _textureID;
	this->rowSize = _rowSize;

	setPositionVector();
	setTextureVector();
}

Tile::Tile(Tile& other)
{
	this->copy(other);
}

Tile::Tile(Tile&& other)
{
	this->move(other);
}

//destructor (empty)
Tile::~Tile(){}

Tile& Tile::operator=(Tile& other)
{
	this->copy(other);
	return *this;
}

Tile& Tile::operator=(Tile&& other)
{
	this->move(other);
	return *this;
}

//method drawing tile on current window
void Tile::draw(const Shader& shader)const
{
	glm::mat4 tileMatrix = glm::mat4(1.0f);
	tileMatrix = glm::translate(tileMatrix, this->tilePositionVector);
	shader.setMat4("tileMatrix", tileMatrix);

	shader.set2Float("transVector",const_cast<glm::vec2&>(this->texturePositionVector));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


//method swapping position's IDs of two tiles
void Tile::swap(Tile &other)
{
	if (this != &other)
	{
		size_t tempID = other.positionID;
		other.positionID = this->positionID;
		this->positionID = tempID;
		other.setPositionVector();
		this->setPositionVector();
	}
}

//method returning tile's position ID
size_t Tile::getPositionID()const
{
	return this->positionID;
}

//method setting tile's position vector
void Tile::setPositionVector()
{
	this->tilePositionVector.x = (positionID % rowSize) / float(rowSize);
	this->tilePositionVector.y = -((positionID / rowSize) / float(rowSize));
	this->tilePositionVector.z = 0;
}

void Tile::setTextureVector()
{
	this->texturePositionVector.x = (textureID % rowSize) / float(rowSize);
	this->texturePositionVector.y = -((textureID / rowSize) / float(rowSize));
}

void Tile::copy(Tile& other)
{
	if (this != &other)
	{
		this->positionID = other.positionID;
		this->textureID = other.textureID;
		this->rowSize = other.rowSize;

		this->setPositionVector();
		this->setTextureVector();
	}
}

void Tile::move(Tile& other)
{
	if (this != &other)
	{
		this->positionID = other.positionID;
		this->textureID = other.textureID;
		this->rowSize = other.rowSize;

		this->setPositionVector();
		this->setTextureVector();
	}
}