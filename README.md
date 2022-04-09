# SwappingGame

## Description

Tiny OpenGL game. The player's goal is to arrange jumbled pieces in the right order to get initial picture. At the start user choose size of board (number of pieces). 
Moving a tile to the empty place is done by pressing *WSAD* or *arrows*.


## Building  (only for Windows)

Clone the repository:

```bash
git clone https://github.com/Aszman/SwappingGame.git
```

Run the compiler in the working directory with command below:

```bash
g++ -std=c++17 -I.\include\ -L.\lib\ .\src\*.cpp .\src\glad.c -lglfw3dll -o .\debug\SwappingGame.exe
```

Run the programm:

```bash
debug\SwappingGame.exe 
```

