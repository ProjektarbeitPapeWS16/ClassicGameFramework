#pragma once
#include "Position.h"
#include "Config.h"

struct Boundaries; // statt class
class Entity;
const unsigned TILECOUNT_DEFAULT = 32; // 32x32 Grid, e.g. for PacMan
const unsigned TILESIZE_DEFAULT = 8; // for Entities with 8x8px Graphics
// Arcade machine resolution in Pixels: 224x256. Translates into 28x32 8px Tiles.

// Purpose: 2D Grid structure that translates a canvas with NxN pixels into subsets of MxM tiles, and vice versa.
//			Used for creating tile-based level design; can translate tile positions into pixel positions.
// Used by: Level.cpp:	To initialize entities at their repsective position in the level.
class Grid 
{
	Boundaries* boundaries; // default: window size?
	unsigned xTileCount; // amount of columns in grid
	unsigned yTileCount; // amount of rows in grid
	unsigned xTileSize; // horizontal grid cell size in Pixels
	unsigned yTileSize; // vertical grid cell size in Pixels

public:
	Grid(unsigned xTileCount = TILECOUNT_DEFAULT, unsigned yTileCount = TILECOUNT_DEFAULT,
			unsigned xTileSize = TILESIZE_DEFAULT, unsigned yTileSize = TILESIZE_DEFAULT);


		// Returns Pixel coordinates for a given Grid coordinate
		Position getCoordinates(unsigned xTilePos, unsigned yTilePos);

		// Centers the position of a given entity at the given grid coordinates.
		// Used by: Level for initialization of all entities for a given level data.
		// Affects: The given Entity
		void setEntityPositionOnGrid(Entity* entity, unsigned xTilePos, unsigned yTilePos);
};

