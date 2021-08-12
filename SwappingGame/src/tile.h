#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>

const int SIZE = 32;

extern int width, height;

const unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3
};


class Tile
{

public:
	Tile(unsigned int = 0, unsigned int = 0);
	Tile(const Tile&);

	Tile& operator=(const Tile&);

	~Tile();

	void draw()const;
	void set(unsigned int, unsigned int);

private:
	GLuint VAO, VBO, EBO;
	unsigned int realID, expectedID;
	float coords[20];
	
	void setTileCoords(float &, float &);
	void setTextCoords(float &, float &);

	void genBuffers();
	void setBuffers();

	void copy(const Tile&);
	void terminate();
};

#endif 
