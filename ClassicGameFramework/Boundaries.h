#pragma once
#include "Position.h"

// Boundaries in pixels, for the level or entities
struct Boundaries
{
	Position position;
	int width;
	int height;

	Boundaries(int x, int y, int width, int height);
};
