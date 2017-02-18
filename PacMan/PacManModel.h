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

	// getter
	//std::vector<Entity*> * getEntities();
	PlayerEntity * getPacman();
	EnemyEntity * getBlueGhost();
	EnemyEntity * getRedGhost();
	EnemyEntity * getOrangeGhost();
	EnemyEntity * getPinkGhost();

private:
	// Attribute
	//Physics * physic;
	//Session * session;
	//Level * level;
	//std::vector<Entity*> * entities;
	int gamecounter = 0;
	int slowit = 0;

	PlayerEntity * pacman;
	EnemyEntity * blueGhost;
	EnemyEntity * redGhost;
	EnemyEntity * orangeGhost;
	EnemyEntity * pinkGhost;

	// Kollisionshandler
	void handleCollisions() override;

	void collisionPacGhost(PhysicalObject * collided);
};

