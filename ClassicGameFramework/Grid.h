#pragma once
#include "Position.h"

struct Boundaries;

const unsigned int COUNT_DEFAULT = 32; // 32x32 Grid, e.g. for PacMan
const unsigned int GRIDSIZE_DEFAULT = 8; // for Entities with 8x8px Graphics

// 2D Grid structure for initial entity positions in a Level
class Grid 
{
	Boundaries* boundaries; // default: window size?
	unsigned int colCount; // amount of columns in grid
	unsigned int rowCount; // amount of rows in grid
	unsigned int xCellSize; // horizontal Cell size in Pixels
	unsigned int yCellSize; // vertical Cell size in Pixels

public:
	Grid(unsigned int colCount = COUNT_DEFAULT, unsigned int rowCount = COUNT_DEFAULT,
			unsigned int xCellSize = GRIDSIZE_DEFAULT, unsigned int yCellSize = GRIDSIZE_DEFAULT);
	~Grid();
	unsigned int getColCount();
	unsigned int getRowCount();
	unsigned int getXCellSize();
	unsigned int getYCellSize();

	// Returns Pixel coordinates for a given Grid coordinate
	Position* getCoordinates(unsigned int xGridPos, unsigned int yGridPos);

	// For creating pixel coordinates with an offset, based on a grid coordinate
	Position* getCoordinates(unsigned int xGridPos, unsigned int yGridPos, int xPixelOffset, int yPixelOffset);
};

