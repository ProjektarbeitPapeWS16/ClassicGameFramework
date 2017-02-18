#pragma once
#include "EngineModel.h"

class PlayerEntity;
class EnemyEntity;
class PhysicalObject;

class PacManModel : public EngineModel
{
public:
	PacManModel();
	
	~PacManModel() override;

	void initialization() override;
	void nextIteration() override;

	// keys
	void static keyUpPress();
	void static keyDownPress();
	void static keyLeftPress();
	void static keyRightPress();
	void static keyEscPress();

	// Hilfe fuer Ghosts TODO ueberdenken
	enum GameState
	{
		STATE_1,
		STATE_2,
		STATE_3,
		STATE_4,
		STATE_5,
		STATE_6
	};

	// getter
	//std::vector<Entity*> * getEntities();
	PlayerEntity * getPacman();
	EnemyEntity * getBlueGhost();

private:
	// Attribute
	GameState state = STATE_1;
	//Physics * physic;
	//Session * session;
	//Level * level;
	//std::vector<Entity*> * entities;
	PlayerEntity * pacman;
	EnemyEntity * blueGhost;

	// Kollisionshandler
	void handleCollisions() override;

	void collisionPacGhost(PhysicalObject * collided);
};

