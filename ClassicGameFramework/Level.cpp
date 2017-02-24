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
	{
		for(size_t i = 0; i < entities->size(); i++)
		{
			delete entities->at(i);
		}
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

// Get reference object for level dimensions
Grid * Level::getGrid() const
{
	return grid;
}

// Get 2D array of level layout (usually derived from external file)
char ** Level::getLevelLayout() const
{
	return levelLayout;
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