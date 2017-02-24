#include "Level.h"
//#include "Physics.h"
#include "Entity.h"
#include "PhysicalObject.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Physics.h"

Level::~Level()
{
	if(physics != nullptr)
	{
		delete physics;
	}

	if (entities != nullptr)
	{ // TODO : Testen ob alle ENtities tatsächlich gelöscht werden
		//for (size_t i = 0; i < entities->size(); i++)
		//{
		//	delete entities->at(i);
		//}
		delete entities;
	}
}
 // Basic constructor for default physics
Level::Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize) :
	Level(colsGrid, rowsGrid, xTileSize, yTileSize, new Physics())
{
}

// Constructor for custom physics
Level::Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, Physics* physics) :
	grid(new Grid(colsGrid, rowsGrid, xTileSize, yTileSize)),
	physics(physics),
	entities(new std::vector<Entity*>())
{
}

Physics* Level::getPhysics() const
{
	return physics;
}

void Level::setPhysics(Physics* physics)
{
	if (this->physics != nullptr)
	{
		delete this->physics;
	}
	this->physics = physics;
}

// Getter for:	Current entities in the level
std::vector<Entity*>* Level::getEntities() const
{
	return entities;
}

// Setter for: Current entities in the level
void Level::setEntities(std::vector<Entity*>* entities)
{
	this->entities = entities;
}

// Get list of all entities' physical properties for collision detection etc
// Used by: physics
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
// Assumes: give textfile has proper syntax to mach a game's level layout.
//		(Correct amount of lines and characters corresponding with
//		level grid; and known entity type symbols.)
char** Level::getLeveldata(const char* filepath, unsigned int rows, unsigned int cols) const
{
	char** array2D = nullptr;
	FILE* file;

	try
	{
		// load levelinfo in binary mode
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
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what(); //TODO: What went wrong?
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
