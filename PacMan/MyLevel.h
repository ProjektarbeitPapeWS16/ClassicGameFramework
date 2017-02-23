#pragma once
#include "Level.h"
#include "Config.h"
class PlayerEntity;
#include "EnemyEntity.h"


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

	bool blinkyOut = false;
	bool pinkyOut = false;
	bool inkyOut = false;
	bool clydeOut = false;

	int dotCounter = 240;
	int energizerCounter = 4;

	int endCounter = 0;
	int gamecounter = 0;
	int slowit = 0;

	__int64 timer = Config::currentTimeMillis();
	__int64 ghostTimer = Config::currentTimeMillis();
	EnemyEntity::MovementMode movementMode = EnemyEntity::SCATTER;
};

