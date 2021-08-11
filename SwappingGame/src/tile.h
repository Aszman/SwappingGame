#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>

const int size = 3;

extern int width, height;

const unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3
};

class Tile
{

private:
	GLuint VAO, VBO, EBO;
	unsigned int realID, expectedID;
	float coords[20];
	
	void setTileCoords(float &, float &);
	void setTextCoords(float &, float &);
	void setBuffers();

	void terminate();

public:

	Tile(unsigned int, unsigned int);
	~Tile();

	void draw()const;
};

#endif 
