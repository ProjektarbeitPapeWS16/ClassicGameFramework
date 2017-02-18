#pragma once
#include "Entity.h"

class Renderer;

class EnemyEntity : public Entity
{
	Image* moveUp1;
	Image* moveUp2;
	Image* moveDown1;
	Image* moveDown2;
	Image* moveRight1;
	Image* moveRight2;
	Image* moveLeft1;
	Image* moveLeft2;
	Image* energized1;
	Image* energized2;
	//Image* dead; TODO

	bool energized;

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
		MOVE_UP_1,
		MOVE_UP_2,
		MOVE_DOWN_1,
		MOVE_DOWN_2,
		DEAD
	};

private: 
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;

public:
	EnemyEntity();
	void request(Request request);
	void execute();
	Image* getImage() override;
};
