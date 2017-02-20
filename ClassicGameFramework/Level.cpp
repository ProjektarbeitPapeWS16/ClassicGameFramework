#include "Level.h"
//#include "Physics.h"
#include "Entity.h"
#include "PhysicalObject.h"
#include "EntityRefTable.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize) :
	grid(new Grid(colsGrid, rowsGrid, xTileSize, yTileSize)),
	entities(new std::vector<Entity*>())
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
// Returns: char** that Stores coordinates of all Level-Info-File symbols to translate into entities in the level
char** Level::getLevelFromFile(std::string* filepath, unsigned int rows = 32, unsigned int cols = 28)
{
	const char IGNORE_AFTER = '"';	// Level-Info-File Symbol	"				used for comments
	const char READ_AFTER = '°';	// Level-Info-File Symbol	°				used for starting level input
	const char IGNORE = ' ';		// Level-Info-File Symbol	(Whitespace)	ignored
	const int MAX = 96;

	int xTileMax = cols;
	int yTileMax = rows;
	char** grid = new char*[rows];	// 2D grid: (for the rows) y pointers to a pointer to (for the columns) the address of an array of size x.
	for (int i = 0; i < rows; i++) {
		grid[i] = new char[cols]; // allocate each row with the respective amount of column entries.
	}
	fopen_s(&file, filepath, "rb");


	bool readLine = false;			// Flag for enabling row input from Level-Info-File
	char rowBuffer[MAX];			// for iterating through tile rows

	try
	{
		auto levelfile = std::ifstream(reinterpret_cast<char*>(filepath));

		if (!levelfile.is_open()) {
			throw 1;
		}

		int row = 0;
		int col = 0;
		std::string test;
		while (!levelfile.eof()) {

			levelfile.getline(rowBuffer, MAX);
			std::string str = rowBuffer;
			if (row < yTileMax) {
				readLine = false;
				col = 0;

				for (std::string::iterator it = str.begin(); it != str.end(); ++it) {

					if (*it != IGNORE && readLine) { // Ignore whitespace
						if (col <= yTileMax) {
							grid[row][col] = *it; // Set tile symbol for grid coordinate
							std::cout << "Symbol at (" << row << "," << col << "): " << *it << ". Added to Grid-Info: " << grid[row][col] << std::endl;
							test += *it;
							++col;
						}
						else {
							std::cout << "Warning: Level layout file contains excess tile information at row " << row << "." << std::endl;
							//#pragma message("Warning: Level layout file contains excess row tile information.")
						}
					}
					else if (*it == READ_AFTER) {
						readLine = true;
						std::cout << "Start reading Line " << row << " now." << std::endl;
					}
					else if (*it == IGNORE_AFTER) {
						readLine = false;
						std::cout << "End reading Line " << row << " now. Read columns: " << col << std::endl;
					}
				}
				if (col > 0) {
					++row;
					if (col < xTileMax) {
						std::cout << "Warning: Row " << row << "only contained " << col << " out of " << xTileMax << " Tiles." << std::endl;
					}
				}
			}
			else {
				std::cout << "Warning: Level layout file contains tile information beyond row " << row << "." << std::endl;
				//#pragma message("Warning: Level layout file contains excess column tile information.")
			}
		}
	}
	catch (int e) {
		std::cout <<  "ERROR::LEVEL::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return grid;
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
	Position entityPos(0,0);						  // initialize at origin; set later
	
	std::vector<PhysicalObject> *result = new std::vector<PhysicalObject>;

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
				Position entityPos = this->grid->getCoordinates(iCol, iRow);
				entity = entityRef->getEntity(typeSymbol, entityPos);
				// 2.3 save entity in vector list using an iterator
				result->vector::push_back(*entity);
			}
		}
	}
	return result;
}

