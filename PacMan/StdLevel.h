#pragma once
#include "Level.h"

class PlayerEntity;

class StdLevel : public Level
{
	PlayerEntity* pacman;

public:
	StdLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path);
	~StdLevel();

	PlayerEntity* getPacman();
};

