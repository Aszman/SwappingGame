#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_s.h"

class Tile
{
public:
	Tile(size_t = 0, size_t = 0, size_t = 1);
	Tile(Tile&);
	Tile(Tile&&);
	~Tile();

	Tile& operator=(Tile&);
	Tile& operator=(Tile&&);

	void draw(const Shader&)const;
	void swap(Tile&);
	size_t getPositionID()const;

private:
	size_t positionID, textureID, rowSize;

	glm::vec3 tilePositionVector;
	glm::vec2 texturePositionVector;

	void setPositionVector();
	void setTextureVector();

	void copy(Tile&);
	void move(Tile&);
};
#endif 