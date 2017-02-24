#pragma once
#include "Level.h"
#include "Physics.h"
#include "HoleEntity.h"
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
	};

private:
	GameConfig* config;
	PlayerEntity* player;
	std::vector<EnemyEntity*>* enemys;
	std::vector<Entity*>* backgroundEntities;
	//Cells* cells;
	UI* ui;
	const char* stageFile;
	//std::vector<PhysicalObject*>* physicalObjects;
	char** leveldata;
	std::vector<HoleEntity*>* holeEntities;
	SpacePanicModel* model;
	void generateSortedEntities() const;
	typedef Level super;
public:

	Stage(SpacePanicModel* model, const char* stageFile);
	~Stage() override;

	

	std::vector<Entity*>* getEntities() const override;
	void setPlayer(PlayerEntity* player);
	void addEnemy(EnemyEntity* enemy) const;
	void addBackgroundEntity(Entity* backgroundEntity) const;
	
	//std::vector<PhysicalObject*>* getPhysicalObjects() const override;

	const char* getFilePath() const;
	PlayerEntity* getPlayer() const;
	std::vector<EnemyEntity*>* getEnemys() const;
	std::vector<Entity*>* getBackgroundEntities() const;

	//Cells* getCells() const;
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* getCollisions() const;
	void addHole(HoleEntity* hole) const;
	void removeHole(HoleEntity* hole) const;
	UI* getUI() const;
	void reset();
	void gameOver();
};
