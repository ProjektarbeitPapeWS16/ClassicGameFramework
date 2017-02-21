#pragma once
#include "Entity.h"
#include "Stage.h"
class SpacePanicModel;

class EnemyEntity : public Entity
{
public:
	typedef enum
	{
		LAUF_1,
		LAUF_2
	} EnemyState;

	
private:
	Stage::Cells::Direction currentRunningDirection;
	EnemyState state;
	unsigned long counter = 0;
	Image* lauf1;
	Image* lauf2;
	SpacePanicModel* model;
	double difficulty;
	Position lastDecision;
public:
	EnemyEntity(SpacePanicModel* model, Position* position, double difficulty);
	Stage::Cells::Direction getRandomAllowedDirection(double row, double column);
	Stage::Cells::Direction getNextRunningDirection(double row, double column);
	void execute();
	
	Image* getImage() override;
};
