#pragma once
#include "EngineModel.h"

class EnemyEntity;
class Physics;
class Entity;
class PlayerEntity;
class PhysicalObject;

class PacManModel : public EngineModel
{
public:
	PacManModel();
	
	std::vector<Entity*> * getEntities();

	~PacManModel() override;
	void initialization() override;
	void nextIteration() override;

	void static keyUpPress();
	void static keyDownPress();
	void static keyLeftPress();
	void static keyRightPress();
	void static keyEscPress();

	enum GameState
	{
		STATE_1,
		STATE_2,
		STATE_3,
		STATE_4,
		STATE_5,
		STATE_6
	};

	PlayerEntity * getPacman();

private:
	GameState state = STATE_1;
	Physics * physic;
	virtual void collisionPacGhost(PhysicalObject * collided);

	std::vector<Entity*> * entities;
	PlayerEntity * pacman;
	EnemyEntity * ghost;
};

