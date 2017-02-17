#include "StdLevel.h"
#include "PlayerEntity.h"



StdLevel::StdLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path)
	: Level(colsGrid, rowsGrid, xTileSize, yTileSize, path)
{
	// TODO Entities erzeugen und dafuer sorgen, dass die View Bescheid weiß
	pacman = new PlayerEntity();
	getEntities()->push_back(*static_cast<Entity*>(pacman));
}


StdLevel::~StdLevel()
{
}

PlayerEntity* StdLevel::getPacman()
{
	return pacman;
}