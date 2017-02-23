#pragma once
#include "Level.h"
#include "Entity.h"

#include "GameConfig.h"
#include "Entity_Jumpman.h" 
#include "Entity_DonkeyKong.h" 
#include "Entity_Barrel.h" 

typedef enum {
	CHAR_JUMPMAN = 'J',
	CHAR_DONKEY_KONG = 'K',
	CHAR_PAULINE = 'P',
	CHAR_LADDER = 'H',
	CHAR_LADDER_BROKEN = 'h',
	CHAR_OIL_DRUM = 'O',

	CHAR_GIRDER = '0',	 // Girder without offset (touches bottom of grid, 9px height)
	CHAR_GIRDER_U1 = '1', // Girder with an offset of 1 pixels upwards
	CHAR_GIRDER_U2 = '2', // Girder with an offset of 2 pixels upwards
	CHAR_GIRDER_U3 = '3', // Girder with an offset of 3 pixels upwards
	CHAR_GIRDER_U4 = '4', // Girder with an offset of 4 pixels upwards
	CHAR_GIRDER_U5 = '5', // Girder with an offset of 5 pixels upwards
	CHAR_GIRDER_U6 = '6', // Girder with an offset of 6 pixels upwards
	CHAR_GIRDER_U7 = '7', // Girder with an offset of 7 pixels upwards
	CHAR_GIRDER_D1 = 'Z', // Girder with an offset of 1 pixels downwards
	CHAR_GIRDER_D2 = 'Y', // Girder with an offset of 2 pixels downwards
	CHAR_GIRDER_D3 = 'X', // Girder with an offset of 3 pixels downwards
	CHAR_GIRDER_D4 = 'W', // Girder with an offset of 4 pixels downwards
	CHAR_GIRDER_D5 = 'V', // Girder with an offset of 5 pixels downwards
	CHAR_GIRDER_D6 = 'U', // Girder with an offset of 6 pixels downwards
	CHAR_GIRDER_D7 = 'T', // Girder with an offset of 7 pixels downwards
} EntityChar;

/// Meant to replicate the first Level of the Donkey Kong arcade game; titled "25m".
class Level_25m : public Level
{
private:
	GameConfig* gameConfig;
	char* FILE_PATH;// = new std::string("levels/Level_25m.txt");
	Entity_Jumpman* player;
	Entity_DonkeyKong* kong;
	std::vector<Entity_Barrel*>* enemies;
	std::vector<Entity*>* backgroundEntities;
	unsigned int jumpStateCount;	// used for determining direction change in jump state.
public:	
	const unsigned int JUMPSTATE_TICKS = 16; // Jumpman can jump 16px high, and will descending after that.

	void setPlayer(Entity_Jumpman* player);
	void addEnemy(Entity_Barrel* enemy) const;
	void addBackgroundEntity(Entity* backgroundEntity) const;

	Level_25m(GameConfig* config);
	~Level_25m() override;
	
	const char* getFilePath() const;
	Entity_Jumpman* getPlayer() const;
	std::vector<Entity_Barrel*>* getEnemies() const;
	std::vector<Entity*>* getBackgroundEntities() const;

};
