#include "tile.h"

Tile::Tile(size_t _positionID,  size_t _textureID, size_t _size)
{
	set(_positionID, _textureID, _size);
}

Tile::~Tile(){}

void Tile::draw(const Shader& shader)
{
	glm::mat4 tileMatrix = glm::mat4(1.0f);
	tileMatrix = glm::translate(tileMatrix, this->tilePositionVector);
	shader.setMat4("tileMatrix", tileMatrix);

	shader.set2Float("transVector", this->texturePositionVector);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tile::set(size_t _positionID, size_t _textureID, size_t _size)
{
	this->positionID = _positionID;
	this->textureID = _textureID;
	this->size = _size;

	this->tilePositionVector.x = (positionID / size) / float(size);
	this->tilePositionVector.y = -((positionID % size) / float(size));
	this->tilePositionVector.z = 0;

	this->texturePositionVector.x = (textureID / size) / float(size);
	this->texturePositionVector.y = -((textureID % size) / float(size));
}