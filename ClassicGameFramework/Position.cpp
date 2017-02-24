#include "Position.h"

Position::Position(int x, int y) : x(x), y(y)
{
}

Position::Position(const Position& other): x(other.x),
                                           y(other.y)
{
}
