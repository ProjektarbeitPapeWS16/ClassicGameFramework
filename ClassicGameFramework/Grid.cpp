#include "Grid.h"
#include "Entity.h"

Grid::Grid(unsigned xCount, unsigned yCount, unsigned xSize, unsigned ySize) : colCount(xCount),
																			   rowCount(yCount),
																			   xCellSize(xSize),
																			   yCellSize(ySize)
{
	/* TODO: Set boundaries based on window bounds (--> max bounds)
	 *this->boundaries->position.x = x[GLFW Window bounds];
	 *this->boundaries->position.y = y[GLFW Window bounds];
	 *	*/
}

Position Grid::getCoordinates(unsigned col, unsigned row)
{
	return Position(this->xCellSize * xGridPos, this->yCellSize * yGridPos);
	//Position pixelPos;
	//pixelPos.x = this->xCellSize * col;
	//pixelPos.y = this->yCellSize * row;
	//return pixelPos;
}

void Grid::setEntityPositionOnGrid(Entity * entity, unsigned col, unsigned row)
{
	//TODO: call entity method to change
	Position pixelPos = getCoordinates(col, row);
	// entity->setPosition(pixelPos.x, pixelPos.y); // somewhat convoluted; created overloaded method with Position parameter instead:
	entity->setPosition(pixelPos);
}
