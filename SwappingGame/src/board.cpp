#include "board.h"

const char* vertexPath = "src/Shaders/vertexShader.vert";
const char* fragmentPath = "src/Shaders/fragmentShader.frag";


//constructor 
Board::Board(size_t _rowSize) : rowSize(_rowSize), tilesAmount(_rowSize*_rowSize), shader(vertexPath, fragmentPath), tileHeight(1 / float(rowSize)), tileWidth(1 / float(rowSize))
{
	up = down = left = right = false;
	
	setCoords();
	setBuffers();

	tiles = new Tile[tilesAmount - 1];
	
	randomize();

	blankTile = Tile(tilesAmount - 1, tilesAmount - 1, rowSize);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f);

	this->shader.use();
	this->shader.setMat4("projection", projection);
	this->shader.setMat4("view", view);
}

//destructor
Board::~Board()
{
	delete[] this->tiles;

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);

	this->shader.terminate();
}

//method drawing board on current window
void Board::draw()const
{
	glBindVertexArray(this->VAO);

	this->shader.use();
	this->shader.setFloat("alpha", 1.0f);

	for (size_t i = 0; i < this->tilesAmount - 1; ++i)
	{
		this->tiles[i].draw(this->shader);
	}

	this->shader.setFloat("alpha", 0.0f);

	blankTile.draw(this->shader);
}

//method finding tile on board with passed position ID
//Get: position ID of searching tile
//Give: reference to searching tile
//Error: when ID doesn't exist return blankTile
Tile& Board::find(size_t positionID)
{
	for (int i = 0; i < this->tilesAmount - 1; ++i)
	{
		if (this->tiles[i].getPositionID() == positionID)
		{
			return this->tiles[i];
		}
	}
	return this->blankTile;
}

//method managing moving around board by blank tile
void Board::move(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && this->up == false)
	{
		if (this->blankTile.getPositionID() < this->tilesAmount - this->rowSize)
		{
			blankTile.swap(this->find(this->blankTile.getPositionID() + this->rowSize));
			this->up = true;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && this->up == true)
	{
		this->up = false;
	}

	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && this->down == false)
	{
		if (this->blankTile.getPositionID() >= this->rowSize)
		{
			blankTile.swap(this->find(this->blankTile.getPositionID() - this->rowSize));
			this->down = true;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE && this->down == true)
	{
		this->down = false;
	}

	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && this->right == false)
	{
		if (this->blankTile.getPositionID() % this->rowSize != 0)
		{
			blankTile.swap(this->find(this->blankTile.getPositionID() - 1));
			this->right = true;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && this->right == true)
	{
		this->right = false;
	}

	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && this->left == false)
	{
		if (this->blankTile.getPositionID() % this->rowSize != this->rowSize - 1)
		{
			blankTile.swap(this->find(this->blankTile.getPositionID() + 1));
			this->left = true;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE && this->left == true)
	{
		this->left = false;
	}
}

//method which permanently sets size of tile and texture's fragment
void Board::setCoords()
{
	//x
	this->tileData[0] = this->tileData[3] = 0.0f;
	this->tileData[6] = this->tileData[9] = this->tileWidth;

	//y
	this->tileData[1] = this->tileData[10] =  1 - this->tileHeight;
	this->tileData[4] = this->tileData[7] = 1.0f;

	//z
	this->tileData[2] =	this->tileData[5] = this->tileData[8] = this->tileData[11] = 0.0f;
}

//method which permanently sets buffers
void Board::setBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->tileData), this->tileData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

//method to ranodmize tiles 
void Board::randomize()
{
	std::srand(unsigned(std::time(0)));

	size_t* temp = new size_t[this->tilesAmount - 1];
	for (int i = 0; i < this->tilesAmount - 1; ++i)
	{
		temp[i] = i;
	}

	do
	{
		std::random_shuffle(temp, temp + this->tilesAmount - 1, Board::myrandom);
	} while (!Board::solvable(temp, this->tilesAmount - 1));

	for (int i = 0; i < this->tilesAmount - 1; ++i)
	{
		tiles[i] = Tile(i, temp[i], this->rowSize);
	}

	delete[] temp;
}

//randomizing core
int Board::myrandom(int i)
{
	return std::rand() % i;
}


//method checking if board is solvable
//Get: array of texture IDs; length of array
//Give: True - is solvable; False - is not
bool Board::solvable(size_t* array, size_t size)
{
	int count = 0;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (array[i] > array[j])
			{
				++count;
			}
		}
	}
	return count % 2 == 0 ? true : false;
}