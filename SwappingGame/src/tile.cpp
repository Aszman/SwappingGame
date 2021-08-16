#include "tile.h"

Tile::Tile(size_t _positionID,  size_t _textureID, size_t _rowSize)
{
	set(_positionID, _textureID, _rowSize);
}

Tile::~Tile(){}

void Tile::draw(const Shader& shader)const
{
	glm::mat4 tileMatrix = glm::mat4(1.0f);
	tileMatrix = glm::translate(tileMatrix, this->tilePositionVector);
	shader.setMat4("tileMatrix", tileMatrix);

	shader.set2Float("transVector",const_cast<glm::vec2&>(this->texturePositionVector));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tile::set(size_t _positionID, size_t _textureID, size_t _rowSize)
{
	this->positionID = _positionID;
	this->textureID = _textureID;
	this->rowSize = _rowSize;

	this->setPosition();

	this->texturePositionVector.x = (textureID % rowSize) / float(rowSize);
	this->texturePositionVector.y = -((textureID / rowSize) / float(rowSize));
}

void Tile::swap(Tile &other)
{
	size_t temp = other.positionID;
	other.positionID = this->positionID;
	this->positionID = temp;
	other.setPosition();
	this->setPosition();
}

size_t Tile::getPositionID()const
{
	return this->positionID;
}

void Tile::setPosition()
{
	this->tilePositionVector.x = (positionID % rowSize) / float(rowSize);
	this->tilePositionVector.y = -((positionID / rowSize) / float(rowSize));
	this->tilePositionVector.z = 0;
}