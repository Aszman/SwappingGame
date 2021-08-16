#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "shader_s.h"

class Tile
{
public:
	Tile(size_t = 0, size_t = 0, size_t = 1);
	~Tile();

	void draw(const Shader&)const;
	void set(size_t, size_t, size_t);
	void swap(Tile&);
	size_t getPositionID()const;

private:
	size_t positionID, textureID, rowSize;

	glm::vec3 tilePositionVector;
	glm::vec2 texturePositionVector;


	void setPosition();
};
#endif 