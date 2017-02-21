#pragma once
#include "Level.h"
class PlayerEntity;
class EnemyEntity;


class MyLevel :
	public Level
{
public:
	MyLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize);
	~MyLevel();

	void gameLoop();
	void handleCollisions();

	PlayerEntity * getPacman();
	EnemyEntity * getBlueGhost();
	EnemyEntity * getRedGhost();
	EnemyEntity * getOrangeGhost();
	EnemyEntity * getPinkGhost();

	enum GameState
	{
		NORMAL,
		PACMANDEAD,
		PACMANxWALL,
		RESTARTGAME
	};

	GameState gameState;

private:
	PlayerEntity* pacman;
	EnemyEntity* blueGhost;
	EnemyEntity* redGhost;
	EnemyEntity* orangeGhost;
	EnemyEntity* pinkGhost;

	int endCounter = 0;
	int gamecounter = 0;
	int slowit = 0;
};

