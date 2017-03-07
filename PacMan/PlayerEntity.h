#pragma once
#include "Entity.h"
#include <vector>

class Image;
class Renderer;

class PlayerEntity : public Entity
{

public:
	enum PlayerState
	{
		NONE,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		DIE,
		DEAD
	};

	PlayerEntity(Boundaries* boundaries);
	void request(PlayerState request);
	void requestPuffer();
	void requestMemory();
	void setMemoryRequest();
	void execute();
	void stepBack();
	Image* getImage() override;
	PlayerEntity::PlayerState getState();
	~PlayerEntity();

	void alternateMovement();

private:
	Image* none;
	Image* move;
	Image* moveUp;
	Image* moveDown;
	Image* moveRight;
	Image* moveLeft;
	Image* pacmanDeath[9];

	PlayerState state = MOVE_DOWN;
	PlayerState memoryState = MOVE_DOWN;
	PlayerState lastRequest = NONE;
	PlayerState pufferRequest = NONE;
	PlayerState memoryRequest = NONE;

	Image* deadAnimation();
	int animationCounter = 0;

	bool alternate = true;
};
