#pragma once
#include "Position.h"
#include "Config.h"

class Boundaries;
class Entity;
const unsigned COUNT_DEFAULT = 32; // 32x32 Grid, e.g. for PacMan
const unsigned GRIDSIZE_DEFAULT = 16; // for Entities with 16x16px Graphics

// 2D Grid structure for initial entity positions in a Level
class Grid 
{
	Boundaries* boundaries; // default: window size?
	unsigned colCount; // amount of columns in grid
	unsigned rowCount; // amount of rows in grid
	unsigned xCellSize; // horizontal Cell size in Pixels
	unsigned yCellSize; // vertical Cell size in Pixels

public:
	Grid(unsigned colCount = COUNT_DEFAULT, unsigned rowCount = COUNT_DEFAULT,
			unsigned xCellSize = GRIDSIZE_DEFAULT, unsigned yCellSize = GRIDSIZE_DEFAULT);


		// Returns Pixel coordinates for a given Grid coordinate
		Position getCoordinates(unsigned xGridPos, unsigned yGridPos);

		// Centers the position of a given entity at the given grid coordinates.
		// Used by: Level for initialization of all entities for a given level data.
		// Affects: The given Entity
		void setEntityPositionOnGrid(Entity* entity, unsigned col, unsigned row);
};

