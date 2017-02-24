#pragma once
#include "Entity.h"

class GameConfig;

class Entity_Barrel : public Entity
{
public:
	typedef enum
	{
		ROLL_RIGHT,
		ROLL_LEFT,
		ROLL_DOWN,
		FALL_DOWN,
	} State;
private:
	State state;
	unsigned long counter = 0;
	Image * img;
public:
	Entity_Barrel(GameConfig* config, Position* position);
	void execute();
	Image* spritesheet;

	Image* getImage() override;
};
