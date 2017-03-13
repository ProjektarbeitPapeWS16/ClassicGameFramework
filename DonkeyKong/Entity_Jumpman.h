#pragma once
#include "Entity.h"

class GameConfig;

class Entity_Jumpman : public Entity
{
	//Image* sprites;	//Spritesheet containing all sprites
	//int* animationStateCycleCount; // = { 2, 3, 4, 3 };
	//const static int stateSpriteCount = 4;

	Image* moveRight1;
	Image* moveRight2;
	Image* moveRight3;
	Image* moveLeft1;
	Image* moveLeft2;
	Image* moveLeft3;
	Image* climb1;
	Image* climb2;
	Image* climbEnd1;
	Image* climbEnd2;
	Image* climbEnd3;
	Image* jumpLeft;
	Image* jumpRight;
	Image* fallLeftEnd;
	Image* fallRightEnd;
	Image* death1;
	Image* death2;
	Image* death3;
	Image* death4;
	Image* death5;

	unsigned int animationStateCount;	// used for determining walking sprites
	unsigned int jumpStateCount;	// used for determining direction change in jump state.
	const unsigned int JUMPSTATE_TICKS = 16; // Jumpman can jump 16px high, and will descend after that.
public:
	enum PlayerState
	{
		MOVE_RIGHT,
		MOVE_LEFT,
		CLIMB,
		CLIMB_DONE,
		JUMP,		// jump straight
		JUMP_LEFT,	// jump left
		JUMP_RIGHT, // jump right
		FALL,		// falls (can have different sprites)
		DEAD,
	};
private:
	PlayerState state = MOVE_RIGHT;
public:
	explicit Entity_Jumpman(Position position);
	void update(unsigned int xOffset, unsigned int yOffset, PlayerState state);
	bool jumpVelocityLeft() const;
};
