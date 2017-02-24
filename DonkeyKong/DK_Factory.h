#pragma once
#include "Entity.h"
#include "Entity_Barrel.h"

#include "Entity_DonkeyKong.h"
#include "Entity_Girder.h"
#include "Entity_Jumpman.h"
#include "Entity_Ladder.h"
#include "Entity_OilDrum.h"
#include "Entity_Pauline.h"

//Helper class for creating entities for the level.
class DK_Factory 
{
public:
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
private:
	GameConfig* config;	// Grid and window size reference
public:
	// Creates entity of desired type and position for level.
	// Used by: Level classes when loading levelinfo from file.
	Entity* getEntity(char entityChar, GameConfig* config, unsigned int xGridPos, unsigned int yGridPos, int xOffset, int yOffset);

	// Helper function for calculating pixel pos for entities in level.
	Position* getPixelPos(GameConfig* config, unsigned int xGridPos, unsigned int yGridPos, int xOffset, int yOffset);
};


Entity::Entity(Image** image, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed) : image(image),
movementSpeed(movement_speed),
solid(solid),
boundaries(boundaries),
movable(movable),
animationSpeed(animation_speed)
{
}