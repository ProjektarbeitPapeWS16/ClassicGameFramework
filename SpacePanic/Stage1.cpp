#include "Stage1.h"

void Stage1::setPlayer(PlayerEntity* player)
{
	delete this->player;
	this->player = player;
}

void Stage1::addEnemy(EnemyEntity* enemy) const
{
	enemys->push_back(enemy);
}

void Stage1::addBackgroundEntity(Entity* backgroundEntity) const
{
	backgroundEntities->push_back(backgroundEntity);
}

Stage1::Stage1(GameConfig* config): Level(config->getRasterColumnsCount(), config->getRasterRowsCount(), config->getRasterWidth(), config->getRasterHeight(), FILE_PATH),
                                    gameConfig(config),
                                    FILE_PATH("levels/stage1.txt"),
                                    enemys(new std::vector<EnemyEntity*>()),
                                    backgroundEntities(new std::vector<Entity*>()),
                                    allEntities(new std::vector<Entity*>()),
                                    physicalObjects(new std::vector<PhysicalObject*>())
{

}



const char* Stage1::getFilePath() const
{
	return FILE_PATH;
}

PlayerEntity* Stage1::getPlayer() const
{
	return player;
}

std::vector<EnemyEntity*>* Stage1::getEnemys() const
{
	return enemys;
}

std::vector<Entity*>* Stage1::getBackgroundEntities() const
{
	return backgroundEntities;
}

Stage1::~Stage1()
{
}

std::vector<Entity*>* Stage1::getEntities() const
{
	return allEntities;
}

std::vector<PhysicalObject*>* Stage1::getPhysicalObjects()
{
	return physicalObjects;
}
