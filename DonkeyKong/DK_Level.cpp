#include "Font.h"
#include "Text.h"

#include "DK_Level.h"
#include "Entity_Girder.h"
#include "Entity_Ladder.h"


	//backgroundEntities->push_back(backgroundEntity);
	//this->entities->push_back(backgroundEntity);



void DK_Level::initEntities(char ** levelLayout, char ** uiLayout)
{

	// Initialize entity list with info
	//	2.1 add ladders 
	//		extend [unbroken] ladders upwards to next girder
	initEntities_Ladders(levelLayout);
	//	2.2 add girders
	initEntities_Obstacles(levelLayout);
	//	2.3 add other special objects (DK, Jumpman, Pauline, Oildrum)
	initEntities_Others(levelLayout);
	//	2.4 store all in that order in entity-vector (ensures rendering with desired layers) TODO: add layer info for view?
	this->entities = getEntityListSortedByType();
}


void DK_Level::initEntities_Ladders(char ** levelLayout)
{
	bool ladderComplete;
	for (auto row = 0; row < grid->getRowCount(); row++)
	{
		for (auto col = 0; col < grid->getColCount(); col++)
		{
			if (levelLayout[row][col] == EntityChar::CHAR_LADDER)
			{
				this->ladders->push_back(new Entity_Ladder(grid->getCoordinates(row, col)));
				// Create ladder Entity with respective coordinates.
				ladderComplete = false;
				// Then create further ladder entities connecting to the next girder above.
				for (int ladderRow = row - 1; ladderComplete || ladderRow >= 0; ladderRow--) {
					this->ladders->push_back(new Entity_Ladder(grid->getCoordinates(row, col)));
					if (isGirderChar(levelLayout[ladderRow][col])) 
					{
						ladderComplete = true;
					}					
				}
			}
			else if (levelLayout[row][col] == EntityChar::CHAR_LADDER_BROKEN) {
				// Create one ladder entity. TODO: Check next girder and place below?
				this->ladders->push_back(new Entity_Ladder(grid->getCoordinates(row, col)));
			}
		}
	}
}

// Creates girder entities with respective offsets (can overlap with ladders)
void DK_Level::initEntities_Obstacles(char ** levelLayout)
{
	for (auto row = 0; row < grid->getRowCount(); row++)
	{
		for (auto col = 0; col < grid->getColCount(); col++)
		{
			switch (levelLayout[row][col])
			{
			case EntityChar::CHAR_GIRDER:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 0)));
				break;
			case EntityChar::CHAR_GIRDER_U2:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 2)));
				break;
			case EntityChar::CHAR_GIRDER_U3:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 3)));
				break;
			case EntityChar::CHAR_GIRDER_U4:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 4)));
				break;
			case EntityChar::CHAR_GIRDER_U5:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 5)));
				break;
			case EntityChar::CHAR_GIRDER_U6:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 6)));
				break;
			case EntityChar::CHAR_GIRDER_U7:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 7)));
				break;
			}
		}
	}
}

// Assumes: Level layout contains one of each.
void DK_Level::initEntities_Others(char ** levelLayout)
{
	for (auto row = 0; row < grid->getRowCount(); row++)
	{
		for (auto col = 0; col < grid->getColCount(); col++)
		{
			switch (levelLayout[row][col])
			{
			case EntityChar::CHAR_DONKEY_KONG:
				this->kong = new Entity_DonkeyKong(this->grid->getCoordinates(col,row)); //TODO
				break;
			case EntityChar::CHAR_JUMPMAN:
				this->player = new Entity_Jumpman(this->grid->getCoordinates(col, row)); //TODO
				break;
			case EntityChar::CHAR_PAULINE:
				this->pauline = new Entity_Pauline(this->grid->getCoordinates(col, row)); //TODO
				break;
			case EntityChar::CHAR_OIL_DRUM:
				this->oildrum = new Entity_OilDrum(this->grid->getCoordinates(col, row)); //TODO
				break;
			}
		}
	}
}

std::vector<Entity*>* DK_Level::getEntityListSortedByType()
{
	std::vector<Entity*>* result = new std::vector<Entity*>;

	// 1. Add all ladders
	for (auto iter = ladders->begin(); iter != ladders->end(); ++iter) {
		result->push_back(*iter);
	}
	// 2. Add all girders
	for (auto iter = girders->begin(); iter != girders->end(); ++iter) {
		result->push_back(*iter);
	}
	// 3. add special entities
	if (kong != nullptr) result->push_back(kong);
	if (pauline != nullptr) result->push_back(pauline);
	if (oildrum != nullptr) result->push_back(oildrum);
	if (player != nullptr) result->push_back(player);

	// 4. add barrels
	/*for (auto iter = barrels->begin(); iter != barrels->end(); ++iter) {
		result->push_back(*iter);
	}*/
	return result;
}

bool DK_Level::isGirderChar(char c)
{
	switch (c) {
	case EntityChar::CHAR_GIRDER:
	case EntityChar::CHAR_GIRDER_U1:
	case EntityChar::CHAR_GIRDER_U2:
	case EntityChar::CHAR_GIRDER_U3:
	case EntityChar::CHAR_GIRDER_U4:
	case EntityChar::CHAR_GIRDER_U5:
	case EntityChar::CHAR_GIRDER_U6:
	case EntityChar::CHAR_GIRDER_U7:
		return true;
	default:
		return false;
	}
		
}

// Basic constructor for creating level layout based on given files, physics, and config.
DK_Level::DK_Level(char * levelFilepath, char * uiFilepath, Physics * physics, GameConfig * config) :
	Level(config->getRasterColumnsCount(), config->getRasterRowsCount(),
		config->getInternalRasterWidth(), config->getInternalRasterHeight(), physics)
{
	// 1. Get entity layout from file
	this->levelLayout = this->getLeveldata(levelFilepath, config->getRasterRowsCount(), config->getRasterColumnsCount());
	this->uiLayout = this->getLeveldata(uiFilepath, config->getRasterRowsCount(), config->getRasterColumnsCount());
	this->config = config;
	// 2. create entities in layered order by reading layout
	initEntities(levelLayout, uiLayout);
}

DK_Level::~DK_Level()
{
}
