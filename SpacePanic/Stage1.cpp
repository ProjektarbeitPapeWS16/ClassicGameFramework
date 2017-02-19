#include "Stage1.h"
#include "WallEntity.h"
#include "LadderEntity.h"

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
		config->getRasterHeight()
	),
	gameConfig(config),
	FILE_PATH("levels/stage1.txt"),
	player(nullptr),
	enemys(new std::vector<EnemyEntity*>()),
	backgroundEntities(new std::vector<Entity*>())
{
	char** leveldata = this->getLeveldata(FILE_PATH, 22, config->getRasterColumnsCount());
	for (int row = 0, _row = -3; row < 22; row++ , _row++)
	{
		for (int col = 0; col < config->getRasterColumnsCount(); col++)
		{
			switch (leveldata[row][col])
			{
			case 'q':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::LEFT_WALL_1));
				break;
			case 'Q':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::LEFT_WALL_2));
				break;
			case 'w':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::MIDDLE_WALL_1));
				break;
			case 'W':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::MIDDLE_WALL_2));
				break;
			case 'e':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::RIGHT_WALL_1));
				break;
			case 'E':
				addBackgroundEntity(new WallEntity(config, new Position(col, 22 - _row), WallEntity::WallState::RIGHT_WALL_2));
				break;

			case 'P':
				setPlayer(new PlayerEntity(config, new Position(col, 22 - _row)));
				break;

			case 'M':
				addEnemy(new EnemyEntity(config, new Position(col, 22 - _row)));
				break;

			case 'H':
				addBackgroundEntity(new LadderEntity(config, new Position(col, 22 - _row)));
				break;

			default: break;


			}
		}
	}


	//addEnemy()

	//

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
