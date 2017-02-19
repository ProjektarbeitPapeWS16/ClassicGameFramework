#pragma once
#include <string>
#include <vector>
#include "Grid.h"
//class Physics;
class PhysicalObject;
class Entity;

class Level
{
	std::string* path; // to layout info file
	char** leveldata; // 2D array: contains level layout (entity placement + types)
	
	std::vector<PhysicalObject>* entities; // contains all entities with respective position;
										   // derived from leveldata on initialization.
	Grid* grid; // determines dimensions, and grid size
	Physics* physics; // physics for respective level. (currently, there is only one kind)
	
public:
	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path);

	// Purpose: Getter for all entities of a level
	// Used by: Physics
	std::vector<PhysicalObject>* getPhysicalObjects();

	// For initializing leveldata:
	// Gets information of all entities for a level, including type and initial (grid-based) placement
	// This is done by reading a textfile with y rows of x symbols corresponding with a Grid
	// of x columns and y rows.
	char** getLevelFromFile(std::string* filepath, int cols, int rows);

	// returns a levels initial entity data (including type and position)
	// Used by: constructor of level for entity initialization
	// Uses: getLevelFromFile
	std::vector<PhysicalObject>* getEntitiesFromFile(std::string* filepath, int cols, int rows); // TODO: add entity-type-table
};
