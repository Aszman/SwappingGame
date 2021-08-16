#ifndef BOARD_H
#define BOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "tile.h"
#include "shader_s.h"

extern const char* vertexPath;
extern const char* fragmentPath;

const unsigned int indices[] =
{
	0, 1, 2,
	0, 2, 3
};

class Board
{
public:
	Board(size_t);

	~Board();

	void draw()const;

	Tile& find(size_t);

	void move(GLFWwindow*);

private:

	Shader shader;

	Tile* tiles;
	Tile blankTile;

	GLuint VAO, VBO, EBO;

	float tileData[12]; //position of tile and texture on tile;
	const size_t rowSize, tilesAmount;
	float tileWidth, tileHeight;

	bool up, down, left, right;

	void setCoords();
	void setBuffers();
};

#endif 