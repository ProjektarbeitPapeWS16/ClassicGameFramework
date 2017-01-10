#include "Level.h"
#include "Physics.h"
#include "PhysicalObject.h"
#include "EntityRefTable.h"
#include <iostream>
#include <fstream>

Level::Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path) : path(path)
{
	// 1. set Grid. TODO: Overload with Grid parameter?
	this->grid = new Grid(colsGrid, rowsGrid, xTileSize, yTileSize);
	
	// 2. set basic Physics. TODO: add parameter for determining special physics? (with gravity/velocity)
	this->physics = new Physics;
	
	// 3.1 set 2D array with entity data from given file.
	this->leveldata = getLevelFromFile(path, rowsGrid, colsGrid);

	// 3.2 create and store entities according to leveldata
	this->entities = getEntitiesFromFile(path, rowsGrid, colsGrid);
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


// get list of all entities' data for collision detection etc
/*
 *std::vector<PhysicalObject>* Level::getPhysicalObjects()
{
	return nullptr;
}
*/

// opens a text file at given filepath,
// then saves that information in a 2D char array.
// assumes: give textfile has proper syntax
// (correct amount of lines and characters corresponding with
//  level grid; and known entity type symbols.)
char** Level::getLevelFromFile(std::string* filepath, int cols, int rows)
{
	char** array2D = new char*[rows];

	// FILE * file;
	std::string str; //for reading the lines
	char entityCharacter; //for storing the respective character

	try
	{
		//% alt: fopen_s(&file, filepath, "rb"); // try opening file
		auto levelfile = std::ifstream(reinterpret_cast<char*>(filepath));
		if (!levelfile.is_open())
		{
			throw 1;
		}
		
		//% std::ifstream in(filepath);
		
		// read content of file line by line (each one represents a row of the grid)
		for (int iRow = 0; iRow < rows; iRow++)
		{
			array2D[iRow] = new char[cols];
			//% std::getline(in, str);
			std::getline(levelfile, str);
			for (int iCol = 0; iCol < str.length() || iCol < cols; iCol++)
			{
				// read character for respective column in the grid
				entityCharacter = str[iCol];
				//TODO: does this properly store the char?
				array2D[iRow, iCol] = reinterpret_cast<char*>(entityCharacter); 
			}
		}
	}
	catch (int e)
	{
		std::cout << "ERROR::LEVEL::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return array2D;
}

// 1. save level information with entity typesymbols in 2D array.
// 2. for each typesymbol:
// 2.1 create entity using EntityRefTable as reference for type data
// 2.2 set entity position on level by using Grid information
std::vector<PhysicalObject>* Level::getEntitiesFromFile(std::string * filepath, int cols, int rows)
{
	char** leveldata = getLevelFromFile(filepath, cols, rows);
	char typeSymbol;
	EntityRefTable* entityRef = new EntityRefTable(); //TODO: Create one with values
	EntityTypeStats* entityStats;
	Entity* entity;
	Position entityPos;
	std::vector<PhysicalObject>* result = new std::vector<PhysicalObject>;

	for (int iCol = 0; iCol < cols; iCol++)
	{
		for (int iRow = 0; iRow < rows; iRow++)
		{
			typeSymbol = leveldata[iCol][iRow];
			// check if level coordinate isn't empty, i.e. contains an entity
			if (typeSymbol != '\n' && typeSymbol != '\0' && typeSymbol != ' ')
			{
				// 2.1 get info on entity type:
				entityStats = entityRef->getEntityTypeStats(typeSymbol);
				// 2.2 create using entityStats and set position via grid
				entityPos = this->grid->getCoordinates(iCol, iRow);
				entity = entityRef->getEntity(typeSymbol, entityPos);
				// 2.3 save entity in vector list using an iterator
				//result->push_back(entity);
			}
		}
	}
	return result;
}

