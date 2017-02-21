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
	std::vector<Entity_Barrel*>* enemys;
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
	std::vector<Entity_Barrel*>* getEnemys() const;
	std::vector<Entity*>* getBackgroundEntities() const;
	~Level_25m() override;
	//std::vector<PhysicalObject*>* getPhysicalObjects() override;
	//std::vector<Entity*>* getEntities() const;


	Cells* getCells() const;
};
