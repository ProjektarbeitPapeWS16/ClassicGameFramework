#pragma once
#include "Entity.h"
#include <vector>

class Image;
class Renderer;

class PlayerEntity : public Entity
{
	Image* move;
	Image* moveUp;
	Image* moveDown;
	Image* moveRight;
	Image* moveLeft;

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
	PlayerState state = MOVE_DOWN_1;
	Request lastRequest = NONE;

public:
	PlayerEntity(Boundaries* boundaries);
	void request(Request request);
	void execute();
	void stepBack();
	Image* getImage() override;
};
