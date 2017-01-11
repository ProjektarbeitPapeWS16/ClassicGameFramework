#include "Grid.h"

Grid::Grid(unsigned xCount, unsigned yCount, unsigned xSize, unsigned ySize) : colCount(xCount),
																			   rowCount(yCount),
																			   xCellSize(xSize),
																			   yCellSize(ySize)
{
	/* TODO: Set boundaries based on window bounds (--> max bounds)
	 *t
	 *his->boundaries->position.x = x[GLFW Window bounds];
	 *this->boundaries->position.y = y[GLFW Window bounds];
	 *	*/
}

Position Grid::getCoordinates(unsigned xGridPos, unsigned yGridPos)
{
	return Position(this->xCellSize * xGridPos, this->yCellSize * yGridPos);
}
