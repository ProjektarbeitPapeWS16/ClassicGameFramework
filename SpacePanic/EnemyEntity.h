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
		FALLING_LEFT,
		IN_HOLE_WAITING,
		IN_HOLE_CLIMBING,
		DEAD
	} EnemyState;


	virtual void collideWith(PhysicalObject* physicalObject) override;
	void reset();
	EnemyEntity::EnemyState getState() const;
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
	Boundaries* original_boundaries;
	int fallingUntil;
public:
	EnemyEntity(SpacePanicModel* model, Position* position, double difficulty);
	Stage::Cells::Direction getRandomAllowedDirection();
	Stage::Cells::Direction getNextRunningDirection();
	int schrittweite();
	unsigned long movement_counter;
	bool tryFall();
	void execute();

protected:
	SpacePanicModel* getModel() const override;
	Boundaries* getBoundaries() override;
	GameConfig* getConfig() const override;
public:
	Image* getImage() override;


	~EnemyEntity() override;
};
