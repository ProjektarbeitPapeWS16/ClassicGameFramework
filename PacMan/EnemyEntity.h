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
	
	void alternateVar();
	bool alternate = true;

public:
	enum State
	{
		NONE,
		DEAD,
		ENERGIZED,
		CAGED
	};

	enum Direction
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	enum Ghost
	{
		Blinky, // red
		Pinky, // pink
		Inky, // blue
		Clyde // orange
	};

	enum MovementMode
	{
		SCATTER,
		CHASE
	};

private: 
	Ghost name;
	PlayerEntity* pacman;
	EnemyEntity* blinky; // for Inky

	Physics* physics;
	Level* level;
	
	State state = NONE;
	State lastRequest = NONE;

	bool energizeAlt = false;

	MovementMode movementMode = SCATTER;

	// TODO change timers
	__int64 energizerTimer = 0;
	__int64 energizerTimer2 = 0;

	// in which direction should we move?
	void findDirection();
	Direction direction = LEFT;

	// move one unit in the direction
	void move(Direction);
	bool canMove(Direction);

public:
	enum Cage
	{
		IN,
		OUT,
		LEFTPLACE,
		RIGHTPLACE,
		LOCKED, //clever?
		NO
	};
	Cage getCageState();
	void setCageState(Cage);
private:
	Cage cageState = LOCKED;
	void moveInCage();

	void die(); //?

	// calculate target tile
	void findTargetTile();
	Boundaries* targetTile = new Boundaries(0,0,0,0);

	// are we at a crossing?
	bool isCrossing();

	// at specialCrossings, Ghosts cannot move upwards
	bool isSpecialCrossing();

public:
	EnemyEntity();
	EnemyEntity(Boundaries * boundaries);
	void setTextures(char* moveUp1, char* moveUp2, char* moveDown1, char* moveDown2, 
		char* moveRight1, char* moveRight2, char* moveLeft1, char* moveLeft2, 
		char* energized1, char* energized2);

	void request(State request);
	void execute();
	void energize();

	void invertDirection();

	Image* getImage() override;
	EnemyEntity::State getState();
	EnemyEntity::Ghost getName();

	void setName(EnemyEntity::Ghost);
	void setPacman(PlayerEntity*);
	void setBlinky(EnemyEntity*); // only for Inky

	void setPhysics(Physics*);
	void setLevel(Level*);

	void setMovementMode(EnemyEntity::MovementMode);
	void setDirection(Direction);

	// TODO do internally
	bool moveOutOfCage();
};
