#include "board.h"

const char* vertexPath = "src/Shaders/vertexShader.vert";
const char* fragmentPath = "src/Shaders/fragmentShader.frag";

Board::Board(size_t _rowSize) : rowSize(_rowSize), tilesAmount(_rowSize*_rowSize), shader(vertexPath, fragmentPath), tileHeight(1 / float(rowSize)), tileWidth(1 / float(rowSize))
{
	up = down = left = right = false;
	
	setCoords();
	setBuffers();

	tiles = new Tile[tilesAmount - 1];

	for (size_t i = 0; i < tilesAmount - 1; ++i)
	{
		tiles[i].set(i, tilesAmount - i - 2, rowSize);
	}

	blankTile.set(tilesAmount - 1, tilesAmount - 1, rowSize);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f);

	this->shader.use();
	this->shader.setMat4("projection", projection);
	this->shader.setMat4("view", view);
}

Board::~Board()
{
	delete[] this->tiles;

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

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

Tile& Board::find(size_t ID)
{
	for (int i = 0; i < this->tilesAmount - 1; ++i)
	{
		if (this->tiles[i].getPositionID() == ID)
		{
			return this->tiles[i];
		}
	}
}

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