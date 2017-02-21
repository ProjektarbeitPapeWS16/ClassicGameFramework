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
		MOVE_DOWN
	};

	enum GhostState
	{
		MOVE_NONE, 
		MOVE_RIGHT_1,
		MOVE_RIGHT_2,
		MOVE_LEFT_1,
		MOVE_LEFT_2,
		MOVE_UP_1,
		MOVE_UP_2,
		MOVE_DOWN_1,
		MOVE_DOWN_2
	};

	enum SpecialState
	{
		ALIVE,
		DEAD,
		ENERGIZED1,
		ENERGIZED2
	};


private: 
	GhostState state = MOVE_NONE;
	Request lastRequest = NONE;
	SpecialState specialState = ALIVE;

public:
	EnemyEntity();
	EnemyEntity(Boundaries * boundaries);
	void setTextures(char* moveUp1, char* moveUp2, char* moveDown1, char* moveDown2, 
		char* moveRight1, char* moveRight2, char* moveLeft1, char* moveLeft2, 
		char* energized1, char* energized2);
	void request(Request request);
	void setState(GhostState state);
	void specialRequest(SpecialState request);
	void execute();
	void stepBack(); // for collision
	Image* getImage() override;
};
