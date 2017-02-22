#include "Stage.h"
#include "WallEntity.h"
#include "LadderEntity.h"
#include "Session.h"
#include "UI.h"
#include "PlayerEntity.h"
#include "SpacePanicModel.h"
#include "EnemyEntity.h"


void Stage::setPlayer(PlayerEntity* player)
{
	if (this->player != nullptr)
	{
		delete this->player;
	}
	this->player = player;
	this->physicalObjects->push_back(player);
}

void Stage::addEnemy(EnemyEntity* enemy) const
{
	this->enemys->push_back(enemy);
	this->physicalObjects->push_back(enemy);
}

void Stage::addBackgroundEntity(Entity* backgroundEntity) const
{
	backgroundEntities->push_back(backgroundEntity);
	this->physicalObjects->push_back(backgroundEntity);
}

void Stage::generateSortedEntities() const
{
	entities->clear();

	//Hintergrund-Entities
	for (auto i = 0; i < backgroundEntities->size(); i++)
	{
		entities->push_back(backgroundEntities->at(i));
	}

	//Player
	entities->push_back(player);

	//Enemys
	for (auto i = 0; i < enemys->size(); i++)
	{
		entities->push_back(enemys->at(i));
	}

	ui->update();
	//UI
	for (auto i = 0; i < ui->getEntities()->size(); i++)
	{
		entities->push_back(ui->getEntities()->at(i));
	}
}

Stage::Stage(SpacePanicModel* model, const char* stageFile, const char* stageMovementFile):
	Level(
		model->getConfig()->getRasterColumnsCount(),
		model->getConfig()->getRasterRowsCount(),
		model->getConfig()->getRasterWidth(),
		model->getConfig()->getRasterHeight(),
		new Physics(model)
	),
	config(model->getConfig()),
	player(nullptr),
	enemys(new std::vector<EnemyEntity*>()),
	backgroundEntities(new std::vector<Entity*>()),
	ui(new UI(model)),
	stageFile(stageFile),
	stageMovementFile(stageMovementFile),
	physicalObjects(new std::vector<PhysicalObject*>())
{
	leveldata = this->getLeveldata(stageFile, 22, config->getRasterColumnsCount());
	cells = new Cells(config, this->getLeveldata(stageMovementFile, 22, config->getRasterColumnsCount()), 22, config->getRasterColumnsCount());

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
			case 'P': setPlayer(new PlayerEntity(model, new Position(col, 25 - row)));
				break;
			case 'M': addEnemy(new EnemyEntity(model, new Position(col, 25 - row), 0.9));
				break;
			case 'H': addBackgroundEntity(new LadderEntity(config, new Position(col, 25 - row)));
				break;
			default: break;
			}
		}
	}

	auto uiEntities = ui->getEntities();
	for (auto i = 0; i < uiEntities->size(); i++)
	{
		addBackgroundEntity(uiEntities->at(i));
	}
}



const char* Stage::getFilePath() const
{
	return stageFile;
}

PlayerEntity* Stage::getPlayer() const
{
	return player;
}

std::vector<EnemyEntity*>* Stage::getEnemys() const
{
	return enemys;
}

std::vector<Entity*>* Stage::getBackgroundEntities() const
{
	return backgroundEntities;
}

Stage::~Stage()
{
	delete cells;
	delete[] leveldata;
	
}

std::vector<Entity*>* Stage::getEntities() const
{
	generateSortedEntities();
	return super::getEntities();
}

Stage::Cells* Stage::getCells() const
{
	return cells;
}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Stage::getCollisions() const
{
	return getPhysics()->checkCollisions(physicalObjects);
}

Stage::Cells::Cells(GameConfig* config, char** movementData, unsigned rowsCount, unsigned columnsCount) :
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

bool Stage::Cells::canMove(Direction direction, int row, int column) const
{
	if (row < 0 || row >= rowsCount || column < 0 || column >= columnsCount)
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

bool Stage::Cells::canMove(Direction direction, double row, double column) const
{
	row = 25 - row + 0.5;

	int row1, col1;// , row2, col2;
	row1 = row;
	col1 = column;
	//row2 = row + 0.5;
	//col2 = column + 0.5; // TODO?

	return canMove(direction, row1, col1);
}


bool Stage::Cells::canDig(unsigned row, unsigned column) const
{
	return this->possibleDirections[row][column] == LEFT_RIGHT;
}

Stage::Cells::Direction Stage::Cells::getDirectionsOn(int column, int row)
{
	return possibleDirections[column][25 - row];
}
