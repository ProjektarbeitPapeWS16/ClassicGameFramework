﻿#pragma once
#include "Entity.h"


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
		DEAD,
	};
private:
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;
public:
	PlayerEntity(GameConfig* config, Position* position);
	void request(Request request);
	int schrittweite() const;
	bool canMove();
	void execute();
	Image* getImage() override;
};
