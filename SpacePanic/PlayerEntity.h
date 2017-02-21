#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"


class GameConfig;

class PlayerEntity : public Entity
{
	GameConfig* config;

	Image* moveRight1;
	Image* moveRight2;
	Image* moveLeft1;
	Image* moveLeft2;
	Image* climb1;
	Image* climb2;
	Image* deadLeft;
	Image* deadRight;
	Image* deadLadder;
	Image* digLeft1;
	Image* digLeft2;
	Image* digRight1;
	Image* digRight2;
	unsigned long long deadSince = 0L;
	SpacePanicModel* model;
public:
	enum Request
	{
		NONE,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		DO_ACTION
	};

	enum PlayerState
	{
		MOVE_RIGHT_1,
		MOVE_RIGHT_2,
		MOVE_LEFT_1,
		MOVE_LEFT_2,
		CLIMB_1,
		CLIMB_2,
		DIG_LEFT_1,
		DIG_LEFT_2,
		DIG_RIGHT_1,
		DIG_RIGHT_2,
		DEAD_RIGHT,
		DEAD_LEFT,
		DEAD_LADDER,
	};
private:
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;
public:
	PlayerEntity(SpacePanicModel* model, Position* position);
	void request(Request request);
	int schrittweite() const;
	bool canMove();
	void execute();
	Image* getImage() override;
	bool isDead() const;

	void collideWith(PhysicalObject* physicalObject) override;
	unsigned long long getDeadSince() const;
};
