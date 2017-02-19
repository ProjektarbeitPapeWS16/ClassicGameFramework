#include "Stage1.h"
#include "WallEntity.h"
#include "LadderEntity.h"
#include "Font.h"
#include "Text.h"

Stage1::Cells* Stage1::getCells() const
{
	return cells;
}

Stage1::Cells::Cells(GameConfig* config, char** movementData, unsigned rowsCount, unsigned columnsCount): 
possibleDirections(new Direction*[rowsCount]), 
config(config), rowsCount(rowsCount), columnsCount(columnsCount)
{
	for (unsigned row = 0; row < rowsCount; row++)
	{
		possibleDirections[row] = new Direction[columnsCount];
		for (unsigned column = 0; column < columnsCount; column++)
		{
			possibleDirections[row][column] = static_cast<Direction>(movementData[row][column]);
		}
	}
}

bool Stage1::Cells::canMove(Direction direction, int row, int column) const
{
	if(row < 0 || row >= rowsCount || column < 0 || column >= columnsCount)
	{
		return false;
	}

	switch (direction)
	{
	case UP:
		switch (possibleDirections[row][column])
		{
		case UP:
		case UP_RIGHT:
		case UP_LEFT:
		case UP_LEFT_RIGHT:
		case UP_DOWN:
		case UP_DOWN_RIGHT:
		case UP_DOWN_LEFT:
		case ALL: return true;
		default: return false;
		}
	case RIGHT:
		switch (possibleDirections[row][column])
		{
		case RIGHT:
		case LEFT_RIGHT:
		case DOWN_RIGHT:
		case DOWN_LEFT_RIGHT:
		case UP_RIGHT:
		case UP_LEFT_RIGHT:
		case UP_DOWN_RIGHT:

		case ALL: return true;
		default: return false;
		}
	case LEFT:
		switch (possibleDirections[row][column])
		{
		case LEFT:
		case LEFT_RIGHT:
		case DOWN_LEFT:
		case DOWN_LEFT_RIGHT:
		case UP_LEFT:
		case UP_LEFT_RIGHT:
		case UP_DOWN_LEFT:
		case ALL: return true;
		default: return false;
		}
	case DOWN:
		switch (possibleDirections[row][column])
		{
		case DOWN:
		case DOWN_RIGHT:
		case DOWN_LEFT:
		case DOWN_LEFT_RIGHT:
		case UP_DOWN:
		case UP_DOWN_RIGHT:
		case UP_DOWN_LEFT:
		case ALL: return true;
		default: return false;
		}
	default: return false;
	}
}

bool Stage1::Cells::canMove(Direction direction, double row, double column) const
{
	row = 25 - row+0.5;

	int row1, col1, row2, col2;
	row1 = row;
	col1 = column;
	row2 = row + 0.5;
	col2 = column + 0.5;

	return canMove(direction, row1, col1);
}

bool Stage1::Cells::canDig(unsigned row, unsigned column) const
{
	return this->possibleDirections[row][column] == LEFT_RIGHT;
}

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
	cells = new Cells(config, this->getLeveldata("levels/stage1_movement.txt", 22, config->getRasterColumnsCount()), 22, config->getRasterColumnsCount());

	for (auto row = 0; row < 22; row++)
	{
		for (auto col = 0; col < config->getRasterColumnsCount(); col++)
		{
			switch (leveldata[row][col])
			{
			case 'q': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::LEFT_WALL_1));
				break;
			case 'Q': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::LEFT_WALL_2));
				break;
			case 'w': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::MIDDLE_WALL_1));
				break;
			case 'W': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::MIDDLE_WALL_2));
				break;
			case 'e': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::RIGHT_WALL_1));
				break;
			case 'E': addBackgroundEntity(new WallEntity(config, new Position(col, 25 - row), WallEntity::WallState::RIGHT_WALL_2));
				break;
			case 'P': setPlayer(new PlayerEntity(config, new Position(col, 25 - row)));
				break;
			case 'M': addEnemy(new EnemyEntity(config, new Position(col, 25 - row)));
				break;
			case 'H': addBackgroundEntity(new LadderEntity(config, new Position(col, 25 - row)));
				break;
			default: break;
			}
		}
	}


	auto font = new Font("fonts/normal/", 8, 8, 200, 80, 0);
	auto text = new Text(config, font, "SPACE PANIC", new Position(6, 30), config->applyFactor(1), 255, 0, 0);
	addBackgroundEntity(text);
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
