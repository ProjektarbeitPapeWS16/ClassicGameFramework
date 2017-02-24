#pragma once
#include "Entity.h"

class GameConfig;

class Entity_DonkeyKong : public Entity
{
public:
	typedef enum
	{
		STAND,		// 2 animation steps
		POUNDCHEST,	// 2 animation steps
		THROWBARREL_DOWN, // 1 sprite
		THROWBARREL_RIGHT, // 1 sprite
	} State;
private:
	State state;
	unsigned long counter = 0;
public:
	Entity_DonkeyKong(Position* position);
	void execute();
	Image* spritesheet;	// col1: stand, col2: pound chest, col3: throwbarrel down, col4: throwbarrel right
	Image* getImage() override;
};
