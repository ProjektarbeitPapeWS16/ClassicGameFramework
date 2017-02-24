#pragma once
#include "Entity.h"

class GameConfig;

class Entity_Jumpman : public Entity
{
	GameConfig* config;

	Image* sprites;	//Spritesheet containing all sprites
	int* animationStateCycleCount; // = { 2, 3, 4, 3 };
	const static int stateSpriteCount = 4;

	Image* moveRight1;
	Image* moveRight2;
	Image* moveLeft1;
	Image* moveLeft2;
	Image* climb1;
	Image* climb2;
	Image* dead;
	Image* digLeft1;
	Image* digLeft2;
	Image* digRight1;
	Image* digRight2;

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
		MOVE_RIGHT_1, //TODO: Combine states
		MOVE_RIGHT_2,
		MOVE_LEFT_1,
		MOVE_LEFT_2,
		CLIMB_1,
		CLIMB_2,
		JUMP_LEFT,
		JUMP_RIGHT,
		JUMP_STRIAGHT_LEFT,
		JUMP_STRAIGHT_RIGHT,
		DEAD1,
		DEAD2,
		DEAD3,
		DEAD4
	};
private:
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;
public:
	Entity_Jumpman(Position* position);
	void request(Request request);
	int schrittweite() const;
	bool canMove();
	void execute();
	//Image* getImage() override;
};
