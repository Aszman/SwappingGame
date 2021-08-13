#ifndef BOARD_H
#define BOARD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tile.h"
#include "shader_s.h"

class Board
{
public:
	Board(size_t, const char*, const char*);

	~Board();

	void draw()const;

private:
	Shader shader;
	Tile* tiles;
	const size_t size;

};

#endif 
