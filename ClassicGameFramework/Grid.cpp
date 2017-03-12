#include "Grid.h"
#include "Boundaries.h"

Grid::Grid(unsigned int xCount, unsigned int yCount, unsigned int xSize, unsigned int ySize)
	:  colCount(xCount), rowCount(yCount), xCellSize(xSize), yCellSize(ySize)
{
	this->boundaries = new Boundaries(0,0,xCount * colCount,yCount * rowCount);
	/* TODO: Set boundaries based on window bounds (--> max bounds)
	 *t
	 *his->boundaries->position.x = x[GLFW Window bounds];
	 *this->boundaries->position.y = y[GLFW Window bounds];
	 *	*/
}

Grid::~Grid()
{
}

unsigned int Grid::getColCount() const
{
	return colCount;
}

unsigned int Grid::getRowCount() const
{
	return rowCount;
}

unsigned int Grid::getXCellSize() const
{
	return xCellSize;
}

unsigned int Grid::getYCellSize() const
{
	return yCellSize;
}

// Returns window coordinates for given grid position
Position Grid::getCoordinates(unsigned int xGridPos, unsigned int yGridPos) const
{
	// Note: y-Axis on window is mirrored compared to grid
	return Position(this->xCellSize * xGridPos, this->yCellSize * (rowCount - 1 - yGridPos));
}

Position Grid::getCoordinates(unsigned int xGridPos, unsigned int yGridPos, int xPixelOffset, int yPixelOffset) const
{
	// Note: y-Axis on window is mirrored compared to grid
	return Position(this->xCellSize * xGridPos + xPixelOffset, (this->yCellSize * (rowCount - 1 - yGridPos)) + yPixelOffset);
}
