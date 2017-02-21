#pragma once
#include "Level.h"
#include "Physics.h"
class SpacePanicModel;
class Session;
class GameConfig;
class Entity;
class PlayerEntity;
class EnemyEntity;
class UI;

class Stage : public Level
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
		bool canDig(unsigned row, unsigned column) const;
		Direction getDirectionsOn(int column, int row);
	};

private:
	GameConfig* config;
	PlayerEntity* player;
	std::vector<EnemyEntity*>* enemys;
	std::vector<Entity*>* backgroundEntities;
	Cells* cells;
	UI* ui;
	const char* stageFile;
	const char* stageMovementFile;
	std::vector<PhysicalObject*>* physicalObjects;
	char** leveldata;
	void generateSortedEntities() const;
public:

	Stage(SpacePanicModel* model, const char* stageFile, const char* stageMovementFile);
	~Stage() override;


	void setPlayer(PlayerEntity* player);
	void addEnemy(EnemyEntity* enemy) const;
	void addBackgroundEntity(Entity* backgroundEntity) const;

	const char* getFilePath() const;
	PlayerEntity* getPlayer() const;
	std::vector<EnemyEntity*>* getEnemys() const;
	std::vector<Entity*>* getBackgroundEntities() const;

	Cells* getCells() const;
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* getCollisions() const;
};
