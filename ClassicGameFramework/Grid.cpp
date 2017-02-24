#include "Grid.h"

Grid::Grid(unsigned int xCount, unsigned int yCount, unsigned int xSize, unsigned int ySize)
	:  colCount(xCount), rowCount(yCount), xCellSize(xSize), yCellSize(ySize)
{
	/* TODO: Set boundaries based on window bounds (--> max bounds)
	 *t
	 *his->boundaries->position.x = x[GLFW Window bounds];
	 *this->boundaries->position.y = y[GLFW Window bounds];
	 *	*/
}

Grid::~Grid()
{
}

unsigned int Grid::getColCount()
{
	return colCount;
}

unsigned int Grid::getRowCount()
{
	return rowCount;
}

unsigned int Grid::getXCellSize()
{
	return xCellSize;
}

unsigned int Grid::getYCellSize()
{
	return yCellSize;
}

Position* Grid::getCoordinates(unsigned int xGridPos, unsigned int yGridPos)
{
	return &Position(this->xCellSize * xGridPos, this->yCellSize * yGridPos);
}

Position* Grid::getCoordinates(unsigned int xGridPos, unsigned int yGridPos, int xPixelOffset, int yPixelOffset)
{
	return &Position(this->xCellSize * xGridPos + xPixelOffset, this->yCellSize * yGridPos + yPixelOffset);
}
