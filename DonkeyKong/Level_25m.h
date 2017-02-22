#pragma once
#include "Level.h"
#include "Entity.h"

#include "GameConfig.h"
#include "Entity_Jumpman.h" 
#include "Entity_Barrel.h" 

/// Meant to replicate the first Level of the Donkey Kong arcade game; titled "25m".
class Level_25m : public Level
{
public:
	// For determining entity type when reading the level file.
	typedef enum {
		CHAR_JUMPMAN = 'J',
		CHAR_DONKEY_KONG = 'K',
		CHAR_PAULINE = 'P',
		CHAR_LADDER = 'H',
		CHAR_LADDER_BROKEN = 'h',
		CHAR_OIL_DRUM = 'O',

		CHAR_GIRDER = '0',	 // Girder without offset (touches bottom of grid, 9px height)
		CHAR_GIRDER_U1 = '1', // Girder with an offset of 1 pixels upwards
		CHAR_GIRDER_U2 = '2', // Girder with an offset of 2 pixels upwards
		CHAR_GIRDER_U3 = '3', // Girder with an offset of 3 pixels upwards
		CHAR_GIRDER_U4 = '4', // Girder with an offset of 4 pixels upwards
		CHAR_GIRDER_U5 = '5', // Girder with an offset of 5 pixels upwards
		CHAR_GIRDER_U6 = '6', // Girder with an offset of 6 pixels upwards
		CHAR_GIRDER_U7 = '7', // Girder with an offset of 7 pixels upwards
		CHAR_GIRDER_D1 = 'Z', // Girder with an offset of 1 pixels downwards
		CHAR_GIRDER_D2 = 'Y', // Girder with an offset of 2 pixels downwards
		CHAR_GIRDER_D3 = 'X', // Girder with an offset of 3 pixels downwards
		CHAR_GIRDER_D4 = 'W', // Girder with an offset of 4 pixels downwards
		CHAR_GIRDER_D5 = 'V', // Girder with an offset of 5 pixels downwards
		CHAR_GIRDER_D6 = 'U', // Girder with an offset of 6 pixels downwards
		CHAR_GIRDER_D7 = 'T', // Girder with an offset of 7 pixels downwards
	} EntityChar;
	class Cells
	{
	public:
		typedef enum
		{
			NONE = '-',
			RIGHT = '6',
			LEFT = '4',
			LEFT_RIGHT = 'h',

			DOWN = '2',
			DOWN_RIGHT = '3',
			DOWN_LEFT = '1',
			DOWN_LEFT_RIGHT = 'w',

			UP = '8',
			UP_RIGHT = '9',
			UP_LEFT = '7',
			UP_LEFT_RIGHT = 's',

			UP_DOWN = 'v',
			UP_DOWN_RIGHT = 'a',
			UP_DOWN_LEFT = 'd',
			ALL = '5',
		} Direction;


		Direction** possibleDirections;
		EntityChar entityChar;
		GameConfig* config;
		unsigned rowsCount, columnsCount;
		Cells(GameConfig* config, char** movementData, unsigned rowsCount, unsigned columnsCount);
		bool canMove(Direction direction, int row, int column) const;
		bool canMove(Direction direction, double row, double column) const;
		bool canDig(unsigned i, unsigned i1) const;
	};

private:
	GameConfig* gameConfig;
	char* FILE_PATH;// = new std::string("levels/Level_25m.txt");
	Entity_Jumpman* player;
	std::vector<Entity_Barrel*>* enemies;
	std::vector<Entity*>* backgroundEntities;
	Cells* cells;
	//std::vector<Entity*>* allEntities;
	//std::vector<PhysicalObject*>* physicalObjects;

public:
	void setPlayer(Entity_Jumpman* player);
	void addEnemy(Entity_Barrel* enemy) const;
	void addBackgroundEntity(Entity* backgroundEntity) const;

	Level_25m(GameConfig* config);

	const char* getFilePath() const;
	Entity_Jumpman* getPlayer() const;
	std::vector<Entity_Barrel*>* getEnemies() const;
	std::vector<Entity*>* getBackgroundEntities() const;
	~Level_25m() override;
	//std::vector<PhysicalObject*>* getPhysicalObjects() override;
	//std::vector<Entity*>* getEntities() const;


	Cells* getCells() const;
};
