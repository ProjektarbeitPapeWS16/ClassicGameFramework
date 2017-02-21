#include "Boundaries.h"

Boundaries::Boundaries(int x, int y, int width, int height) : Boundaries(x, y, width, height, 0, 0, 0, 0)
{
}

Boundaries::Boundaries(int x, int y, int width, int height,
                       int off_left,
                       int off_bottom,
                       int off_right,
                       int off_top)
	: position(x, y), width(width), height(height), off_left(off_left), off_right(off_right),
	off_top(off_top),
	off_bottom(off_bottom)
{
	
}

int Boundaries::real_x() const
{
	return position.x + off_left;
}

int Boundaries::real_y() const
{
	return position.y + off_left;
}

int Boundaries::real_width() const
{
	return width - off_left - off_right;
}

int Boundaries::real_height() const
{
	return height - off_bottom - off_top;
}
