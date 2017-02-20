#pragma once
#include "Level.h"
#include "GameConfig.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

class Stage1 : public Level
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
	char* FILE_PATH;// = new std::string("levels/stage1.txt");
	PlayerEntity* player;
	std::vector<EnemyEntity*>* enemys;
	std::vector<Entity*>* backgroundEntities;
	Cells* cells;
	//std::vector<Entity*>* allEntities;
	//std::vector<PhysicalObject*>* physicalObjects;

public:


	void setPlayer(PlayerEntity* player);
	void addEnemy(EnemyEntity* enemy) const;
	void addBackgroundEntity(Entity* backgroundEntity) const;
	Stage1(GameConfig* config);
	const char* getFilePath() const;
	PlayerEntity* getPlayer() const;
	std::vector<EnemyEntity*>* getEnemys() const;
	std::vector<Entity*>* getBackgroundEntities() const;
	~Stage1() override;
	//std::vector<PhysicalObject*>* getPhysicalObjects() override;
	//std::vector<Entity*>* getEntities() const;


	Cells* getCells() const;
};
