#pragma once
#include "Level.h"
#include "Entity.h"

#include "GameConfig.h"
#include "Entity_Jumpman.h" 
#include "Entity_DonkeyKong.h" 
#include "Entity_Barrel.h" 
#include "Entity_Girder.h"
#include "Entity_OilDrum.h"
#include "Entity_Pauline.h"
#include "Entity_Ladder.h"

typedef enum {
	CHAR_JUMPMAN = 'J',
	CHAR_DONKEY_KONG = 'K',
	CHAR_PAULINE = 'P',
	CHAR_LADDER = 'H',
	CHAR_LADDER_BROKEN = 'h',
	CHAR_OIL_DRUM = 'F',

	CHAR_GIRDER = '0',	 // Girder without offset (touches bottom of grid, 9px height)
	CHAR_GIRDER_U1 = '1', // Girder with an offset of 1 pixels upwards
	CHAR_GIRDER_U2 = '2', // Girder with an offset of 2 pixels upwards
	CHAR_GIRDER_U3 = '3', // Girder with an offset of 3 pixels upwards
	CHAR_GIRDER_U4 = '4', // Girder with an offset of 4 pixels upwards
	CHAR_GIRDER_U5 = '5', // Girder with an offset of 5 pixels upwards
	CHAR_GIRDER_U6 = '6', // Girder with an offset of 6 pixels upwards
	CHAR_GIRDER_U7 = '7', // Girder with an offset of 7 pixels upwards
	/*
	CHAR_GIRDER_D1 = 'Z', // Girder with an offset of 1 pixels downwards
	CHAR_GIRDER_D2 = 'Y', // Girder with an offset of 2 pixels downwards
	CHAR_GIRDER_D3 = 'X', // Girder with an offset of 3 pixels downwards
	CHAR_GIRDER_D4 = 'W', // Girder with an offset of 4 pixels downwards
	CHAR_GIRDER_D5 = 'V', // Girder with an offset of 5 pixels downwards
	CHAR_GIRDER_D6 = 'U', // Girder with an offset of 6 pixels downwards
	CHAR_GIRDER_D7 = 'T', // Girder with an offset of 7 pixels downwards
	*/
} EntityChar;

// Meant to replicate the first Level of the Donkey Kong arcade game; titled "25m".
class DK_Level : public Level
{
private:

	// Entity lists for checking through:
	char** uiLayout;				// 2D array containing UI layout.
	GameConfig* config;				//TODO: make consistent [Grid]
	
	//Entities determined by level

	Entity_Jumpman* player;		// Jumpman. Takes inputs from model
	Entity_DonkeyKong* kong;	// Donkey Kong. Spawns barrels.
	Entity_OilDrum* oildrum;	// Oil Drum. Despans barrels [TODO: spawns fire/foxes]
	std::vector<Entity_Barrel*>* barrels;	// Spawned barrels. 
	std::vector<Entity_Ladder*>* ladders;	// Spawned first.
	std::vector<Entity_Girder*>* girders;	// obstacles
	unsigned int jumpStateCount;	// used for determining direction change in jump state.
	const unsigned int JUMPSTATE_TICKS = 16; // Jumpman can jump 16px high, and will descending after that.
	
	//UI Entities [TODO; determined by Session] (only placement and look level-dependant)


	//void setPlayer(Entity_Jumpman* player);
	//void addEnemy(Entity_Barrel* enemy) const;
	//void addBackgroundEntity(Entity* backgroundEntity) const;
	
	// Helper function. Initializes all entity attributes,
	// then creates an entity vector from them for view and physics;
	// with an order that draws their images in correct order
	void initEntities(char** levelLayout, char** uiLayout);
	
	// Helper function for initEntities.
	// Initializes attribute containing all entities of one particular type,
	// identified by representative character.
	// Affects: Respective attribute containing those entities
	void initEntities_Ladders(char** levelLayout);
	void initEntities_Obstacles(char** levelLayout);
	void initEntities_Others(char** levelLayout);
	bool isGirderChar(char c);	// True, if any char representing a girder in levelLayout
public:			
	// Standard constructor to get information for initializing all entities.
	DK_Level(char* levelFilepath, char* uiFilepath, Physics* physics, GameConfig* config);
	~DK_Level() override;
	
	// main event function. executes respective function for a game loop
	void nextTick();

};
