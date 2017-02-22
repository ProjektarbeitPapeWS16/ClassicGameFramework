#pragma once
#include "Entity.h"

class PlayerEntity;
class Renderer;
class Physics;
class Level;

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
	Image* deadUp;
	Image* deadDown;
	Image* deadRight;
	Image* deadLeft;

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

	enum Ghost
	{
		Blinky, // red
		Pinky, // pink
		Inky, // blue
		Clyde // orange
	};


private: 
	GhostState state = MOVE_NONE;
	Request lastRequest = NONE;
	SpecialState specialState = ALIVE;
	__int64 energizerTimer = 0;
	__int64 energizerTimer2 = 0;

	enum Direction
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	enum MovementMode
	{
		SCATTER,
		CHASE,
		FRIGHTENED
	};
	MovementMode movementMode;

	// move one unit in the direction
	void move(Direction);

	// in which direction should we move?
	void findDirection();
	Direction direction;

	// calculate target tile
	void findTargetTile();
	Boundaries targetTile;

	// are we at a crossing?
	bool isCrossing();

	bool canMove(Direction);

	Ghost name;
	PlayerEntity* pacman;
	EnemyEntity* blinky; // for Inky

	Physics* physics;
	Level* level;

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
	EnemyEntity::SpecialState getSpecialState();
	EnemyEntity::Ghost getName();

	void setName(EnemyEntity::Ghost);
	void setPacman(PlayerEntity*);
	void setBlinky(EnemyEntity*); // only for Inky

	void setPhysics(Physics*);
	void setLevel(Level*);

	EnemyEntity::MovementMode getMovementMode();
	void setMovementMode(EnemyEntity::MovementMode);

	bool moveOutOfCage();
};
