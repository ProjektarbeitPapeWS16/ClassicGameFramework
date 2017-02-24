#include "Font.h"
#include "Text.h"

#include "DK_Level.h"
#include "Entity_Girder.h"
#include "Entity_Ladder.h"


	//backgroundEntities->push_back(backgroundEntity);
	//this->entities->push_back(backgroundEntity);



void DK_Level::initEntities(char ** levelLayout, char ** uiLayout)
{

	// 0. initialize attributes
	// 1. Read file and store layout info
	// 2. Initialize entity list with info
	//	2.1 add ladders 
	//		extend [unbroken] ladders upwards to next girder
	//	2.2 add girders
	//	2.3 add other objects (DK, Jumpman, Pauline)
	//	2.4 store all in that order in entity-vector (ensures rendering with desired layers) TODO: add layer info for view?
	
}


void DK_Level::initEntities_Ladders(char ** levelLayout)
{
	bool ladderComplete;
	for (int row = 0; row < grid->getRowCount; row++)
	{
		for (int col = 0; col < grid->getColCount; col++)
		{
			if (levelLayout[row][col] == EntityChar::CHAR_LADDER)
			{
				// Create Ladder Entity with respective coordinates.
				this->ladders->push_back(Entity_Ladder(config, grid->getCoordinates(row, col));
				ladderComplete = false;
				for (int ladderRow = row; ladderComplete || ladderRow >= 0; ladderRow--) {
					if (isGirderChar(levelLayout[row][col])) 
					{
						ladderRow = true;
					}
					
				}
				// Create ladder, as well as further ladder entities up to the next girder
			}
			else if (levelLayout[row][col] == EntityChar::CHAR_LADDER_BROKEN) {

			}
		}
	}
}

void DK_Level::initEntities_Obstacles(char ** levelLayout)
{
	for (int row = 0; row < grid->getRowCount; row++)
	{
		for (int col = 0; col < grid->getColCount; col++)
		{
			switch (levelLayout[row][col])
			{

			}
		}
	}
}

void DK_Level::initEntities_Others(char ** levelLayout)
{
	for (int row = 0; row < grid->getRowCount; row++)
	{
		for (int col = 0; col < grid->getColCount; col++)
		{
			if(isGirderChar(levelLayout[row][col]))
			{

			}
		}
	}
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
	Level(config->getRasterColumnsCount,config->getRasterRowsCount,config->getInternalRasterWidth,config->getInternalRasterHeight, physics)
{
	// 1. Get entity layout from file
	this->levelLayout = this->getLeveldata(levelFilepath, config->getRasterRowsCount, config->getRasterColumnsCount);
	this->uiLayout = this->getLeveldata(uiFilepath, config->getRasterRowsCount, config->getRasterColumnsCount);
	this->config = config;
	// 2. create entities in layered order by reading layout
	initEntities(levelLayout, uiLayout);
}

DK_Level::~DK_Level()
{
}
