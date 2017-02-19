#include "Level.h"
//#include "Physics.h"
#include "Entity.h"
#include "PhysicalObject.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize) :
	grid(new Grid(colsGrid, rowsGrid, xTileSize, yTileSize)),
	entities(new std::vector<Entity*>())
{
}

// TODO:
// 1 extract i/o method (for bitmaps) as separate routine (available in Config?)
// 2 use to open and read txt-message with level info
// 2.1 check if proper type?
// 3 save text in 2D array (provides initial entity positions)
// 4 add class that returns entity type for a particular symbol in text file
//		( e.g. O --> Player entity		X --> Obstacle		1 --> Ghost "Blinky", etc
// 5 iterate through 2D array: 
// 5.1 for each symbol, determine entity type with mapping class
// 5.2 using Grid, determine position on map
//		(e.g. arraypos[4][5] corresponds with column 4, row 5 of level grid.
//		if grid size is 16px height and width, entity must be centered:
//		xPosition = 5*16 + 16/2, yPosition = 4*16 + 16/2. 
//		Pixel-position in level: (88px, 72px)

std::vector<Entity*>* Level::getEntities() const
{
	return entities;
}

void Level::setEntities(std::vector<Entity*>* entities)
{
	this->entities = entities;
}

// get list of all entities' data for collision detection etc
std::vector<PhysicalObject*>* Level::getPhysicalObjects() const
{
	if (entities)
	{
		auto physicalObjects = new std::vector<PhysicalObject*>;
		for (unsigned int i = 0; i < entities->size(); i++)
		{
			PhysicalObject* phys = entities->at(i);
			physicalObjects->push_back(phys);
		}
		return physicalObjects;
	}
	else
	{
		return nullptr;
	}
}

// opens a text file at given filepath,
// then saves that information in a 2D char array.
// assumes: give textfile has proper syntax
// (correct amount of lines and characters corresponding with
//  level grid; and known entity type symbols.)
char** Level::getLeveldata(const char* filepath, unsigned int rows, unsigned int cols) const
{
	char** array2D = nullptr;
	FILE * file;

	fopen_s(&file, filepath, "rb");



	// read content of textfile line by line
	std::ifstream in(filepath);
	std::string str;
	char entityCharacter;
	array2D = new char*[rows];
	for (auto iRow = 0; iRow < rows; iRow++)
	{
		// load next line of text; which contains one row
		array2D[iRow] = new char[cols];
		std::getline(in, str);
		for (auto iCol = 0; iCol < str.length() || iCol < cols; iCol++)
		{
			entityCharacter = str[iCol];
			array2D[iRow][iCol] = entityCharacter;

		}
	}
	return array2D;
}

/*
// from http://stackoverflow.com/questions/4823177/reading-a-file-character-by-character-in-c 
// checks file length, then reads char by char
char *readFile(char *fileName) {
	FILE *file = fopen(fileName, "r");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL) return NULL; //could not open file
	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	code = malloc(f_size);

	while ((c = fgetc(file)) != EOF) {
		code[n++] = (char)c;
	}

	code[n] = '\0';

	return code;
}*/

/*
Physics* Level::getPhysics()
{
	return physics;
}
*/
