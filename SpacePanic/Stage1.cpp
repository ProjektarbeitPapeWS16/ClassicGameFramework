#include "Stage1.h"
#include "WallEntity.h"

void Stage1::setPlayer(PlayerEntity* player)
{
	if (this->player != nullptr)
	{
		delete this->player;
	}
	this->player = player;
	this->entities->push_back(player);
}

void Stage1::addEnemy(EnemyEntity* enemy) const
{
	this->enemys->push_back(enemy);
	this->entities->push_back(enemy);
}

void Stage1::addBackgroundEntity(Entity* backgroundEntity) const
{
	backgroundEntities->push_back(backgroundEntity);
	this->entities->push_back(backgroundEntity);
}

Stage1::Stage1(GameConfig* config):
	Level(
		config->getRasterColumnsCount(),
		config->getRasterRowsCount(),
		config->getRasterWidth(),
		config->getRasterHeight(),
		new std::string(FILE_PATH)
	),
	gameConfig(config),
	FILE_PATH("levels/stage1.txt"),
	player(nullptr),
	enemys(new std::vector<EnemyEntity*>()),
	backgroundEntities(new std::vector<Entity*>())
{

	//addEnemy()

	//addBackgroundEntity(new WallEntity(config, new Position(config->)));

	//char** leveldata = this->getLeveldata("levels/stage1.txt", 23, config->getRasterColumnsCount());

	
	//addEnemy();
	//setPlayer(new PlayerEntity(config, new Position(config->applyFactor(5), config->applyFactor(5))));
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
