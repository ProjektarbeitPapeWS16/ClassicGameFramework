#pragma once
#include "Level.h"
#include "Config.h"
#include "EnemyEntity.h"

#include "Font.h"
#include "Text.h"

class PlayerEntity;
class WallEntity;
class BonusEntity;

class MyLevel : public Level
{
public:
	MyLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize);
	void initializeLevel();
	void start();
	void restart();
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
		PAUSE,
		PACMANDEAD,
		RESTARTGAME
	};

	GameState gameState; // TODO kommt raus

	GameState getGameStateRequest();

private:
	void createDots();

	void pacManExecution();
	void pacManCollision();
	bool pacManXWall();

	GameState gameStateRequest = NORMAL;

	PlayerEntity* pacman;
	EnemyEntity* blueGhost;
	EnemyEntity* redGhost;
	EnemyEntity* orangeGhost;
	EnemyEntity* pinkGhost;
	std::vector<WallEntity*>* walls;

	Entity* pacLife1;
	Entity* pacLife2;
	Entity* pacLife3;

	BonusEntity* bonus1;
	BonusEntity* bonus2;
	bool bbonus1 = false;
	bool bbonus2 = false;
	__int64 bonusTimer1 = Config::currentTimeMillis();
	__int64 bonusTimer2 = Config::currentTimeMillis();

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


	int score = 0;
	int life = 3;
	void showScore();
	Font* font = new Font("fonts/normal/", 8, 8, 200, 80, 0);
	Text text = Text(font, "0", new Position(24 * 3, 272 * 3), 3, 255, 255, 255);
};

