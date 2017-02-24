#include "Font.h"
#include "Text.h"

#include "Level_25m.h"
#include "Entity_Girder.h"
#include "Entity_Ladder.h"

void Level_25m::setPlayer(Entity_Jumpman* player)
{
	if (this->player != nullptr)
	{
		delete this->player;
	}
	this->player = player;
	this->entities->push_back(player);
}

void Level_25m::addEnemy(Entity_Barrel* enemy) const
{
	this->enemies->push_back(enemy);
	this->entities->push_back(enemy);
}

void Level_25m::addBackgroundEntity(Entity* backgroundEntity) const
{
	backgroundEntities->push_back(backgroundEntity);
	this->entities->push_back(backgroundEntity);
}

Level_25m::Level_25m(GameConfig* config) :
	Level(
		config->getRasterColumnsCount(),
		config->getRasterRowsCount(),
		config->getRasterWidth(),
		config->getRasterHeight()
	),
	gameConfig(config),
	FILE_PATH("levels\\stage1.txt"), // TODO

	player(nullptr),
	enemies(new std::vector<Entity_Barrel*>()),
	backgroundEntities(new std::vector<Entity*>())
{
	char** leveldata = this->getLeveldata(FILE_PATH, 22, config->getRasterColumnsCount());
	//cells = new Cells(config, this->getLeveldata("levels\\stage1_movement.txt", 22, config->getRasterColumnsCount()), 22, config->getRasterColumnsCount());

	for (auto row = 0; row < 22; row++)
	{
		for (auto col = 0; col < config->getRasterColumnsCount(); col++)
		{
			switch (leveldata[row][col])
			{
			//case EntityChar::CHAR_GIRDER: addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::LEFT_WALL_1));
			case 'q': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::LEFT_WALL_1));
				break;
			case 'Q': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::LEFT_WALL_2));
				break;
			case 'w': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::MIDDLE_WALL_1));
				break;
			case 'W': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::MIDDLE_WALL_2));
				break;
			case 'e': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::RIGHT_WALL_1));
				break;
			case 'E': addBackgroundEntity(new Entity_Girder(config, new Position(col, 25 - row), Entity_Girder::WallState::RIGHT_WALL_2));
				break;
			case 'P': setPlayer(new Entity_Jumpman(config, new Position(col, 25 - row)));
				break;
			case 'M': addEnemy(new Entity_Barrel(config, new Position(col, 25 - row)));
				break;
			case 'H': addBackgroundEntity(new Entity_Ladder(config, new Position(col, 25 - row)));
				break;
			default: break;
			}
		}
	}


	auto font = new Font("fonts\\normal\\", 8, 8, 200, 80, 0);
	//auto text = new Text(config, font, "DONKEY KONG", new Position(6, 30), config->applyFactor(1), 255, 0, 0);
	//addBackgroundEntity(text);
}


const char* Level_25m::getFilePath() const
{
	return FILE_PATH;
}

Entity_Jumpman* Level_25m::getPlayer() const
{
	return player;
}

std::vector<Entity_Barrel*>* Level_25m::getEnemies() const
{
	return enemies;
}

std::vector<Entity*>* Level_25m::getBackgroundEntities() const
{
	return backgroundEntities;
}

Level_25m::~Level_25m()
{
}
