#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"
#include "MovableEntity.h"


class GameConfig;

class PlayerEntity : public MovableEntity
{
	GameConfig* config;

private:
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

	unsigned long  cycle_counter = 0;
	Boundaries* original_boundaries;
public:
	enum Request
	{
		NONE,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		DIG,
		UNDIG
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
		FALLING_RIGHT,
		FALLING_LEFT,
	};

private:
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;
public:
	PlayerEntity(SpacePanicModel* model, Position* position);
	void request(Request request);
	int schrittweite() const;
	bool canMove();
	bool dig() const;
	bool unDig() const;
	int fallingUntil;
	//static int until;
	//static unsigned long long lastMovement;
	//static unsigned long movement_counter;
	bool canDig() const;
	bool canUnDig() const;
	bool tryFall();
	void execute();
	Image* getImage() override;
	bool isDead() const;
	void reset();

protected:
	SpacePanicModel* getModel() const override;
	GameConfig* getConfig() const override;
	void setPosition(int xPos, int yPos) override;
public:
	~PlayerEntity() override;
	void collideWith(PhysicalObject* physicalObject) override;
	unsigned long long getDeadSince() const;
	Boundaries* getBoundaries() override;
};
