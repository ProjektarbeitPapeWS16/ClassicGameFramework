#pragma once
#include "Level.h"
#include "GameConfig.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

class Stage1 : public Level
{
	GameConfig* gameConfig;
	char* FILE_PATH;// = new std::string("levels/stage1.txt");
	PlayerEntity* player;
	std::vector<EnemyEntity*>* enemys;
	std::vector<Entity*>* backgroundEntities;
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
};
