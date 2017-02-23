#pragma once
#include "Entity.h"
#include "Stage.h"
#include "MovableEntity.h"
class SpacePanicModel;

class EnemyEntity : public MovableEntity
{
public:
	typedef enum
	{
		LAUF_1,
		LAUF_2,
		FALLING,
		IN_HOLE_WAITING,
		IN_HOLE_CLIMBING
	} EnemyState;


	virtual void collideWith(PhysicalObject* physicalObject) override;
private:
	Stage::Cells::Direction currentRunningDirection;
	EnemyState state;
	unsigned long counter = 0;
	Image* lauf1;
	Image* lauf2;
	SpacePanicModel* model;
	double difficulty;
	Position lastDecision;
	HoleEntity::HoleState inHole;
	long long inHoleWaitingSince;
public:
	EnemyEntity(SpacePanicModel* model, Position* position, double difficulty);
	Stage::Cells::Direction getRandomAllowedDirection();
	Stage::Cells::Direction getNextRunningDirection();
	void execute();

protected:
	SpacePanicModel* getModel() const override;
	Boundaries* getBoundaries() override;
	GameConfig* getConfig() const override;
public:
	Image* getImage() override;


	~EnemyEntity() override;
};
