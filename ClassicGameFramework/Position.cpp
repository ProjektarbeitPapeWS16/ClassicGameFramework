#include "Position.h"

Position::Position(int x, int y) : x(x), y(y)
{
}

void Position::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
