#ifndef TILE_H
#define TILE_H

#include <glad/glad.h>

extern int width, height;

const unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3
};


class Tile
{

public:
	Tile(size_t = 0, size_t = 0, size_t = 1);
	Tile(const Tile&);

	Tile& operator=(const Tile&);

	~Tile();

	void draw()const;
	void set(size_t, size_t, size_t);

private:
	GLuint VAO, VBO, EBO;
	size_t realID, expectedID, size;
	float coords[20];
	
	void setTileCoords(float &, float &);
	void setTextCoords(float &, float &);

	void genBuffers();
	void setBuffers();

	void copy(const Tile&);
	void terminate();
};

#endif 
