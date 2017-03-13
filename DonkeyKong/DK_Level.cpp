#include "Font.h"
#include "Text.h"

#include "DK_Level.h"
#include "DK_Model.h"
#include "Entity_Girder.h"
#include "Entity_Ladder.h"
#include "Physics.h"

#include <fstream>
#include "../SpacePanic/LadderEntity.h"


//backgroundEntities->push_back(backgroundEntity);
	//this->entities->push_back(backgroundEntity);

/// Helper Methods for initialization:

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

// Assumes: levelLayout is 2D array with [DK_cols, DK_rows]
// Sets ladder entities of a level.
// Affects:	ladders
void DK_Level::initEntities_Ladders(char ** levelLayout)
{
	this->ladders = new std::vector<Entity_Ladder*>;
	bool ladderComplete;
	for (auto row = 0; row < grid->getRowCount(); row++)
	{
		for (auto col = 0; col < grid->getColCount(); col++)
		{
			if (levelLayout[row][col] == EntityChar::CHAR_LADDER)
			{
				// Initiate ladder Entity creation at respective coordinate...
				ladderComplete = false;
				for (auto ladderRow = row; !ladderComplete; ladderRow--) {
					//...and keep creating ladders while moving upwards on grid...
					this->ladders->push_back(new Entity_Ladder(grid->getCoordinates(col, ladderRow)));
					//...until one connects with a girder (or top of level), and the ladder is complete.
					if (isGirderChar(levelLayout[ladderRow][col]) || ladderRow<=0) 
					{
						ladderComplete = true;
					}					
				}
			}
			else if (levelLayout[row][col] == EntityChar::CHAR_LADDER_BROKEN) {
				// Create one ladder entity. TODO: Check next girder and place below?
				this->ladders->push_back(new Entity_Ladder(grid->getCoordinates(col,row)));
			}
		}
	}
}

// Creates girder entities with respective offsets (can overlap with ladders)
void DK_Level::initEntities_Obstacles(char ** levelLayout)
{
	this->girders = new std::vector<Entity_Girder*>;
	for (auto row = 0; row < grid->getRowCount(); row++)
	{
		for (auto col = 0; col < grid->getColCount(); col++)
		{
			switch (levelLayout[row][col])
			{
			case EntityChar::CHAR_GIRDER:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 0)));
				break;
			case EntityChar::CHAR_GIRDER_U1:
				this->girders->push_back(new Entity_Girder(grid->getCoordinates(col, row, 0, 1)));
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
			default:
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
				this->adjustPosition(kong);	// Move upwards to stand on girders.
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
			default:
				break;
			}
		}
	}
}

std::vector<Entity*>* DK_Level::getEntityListSortedByType() const
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

// Used for determining where to end ladders
bool DK_Level::isGirderChar(char c)
{
	switch (c) {
	case CHAR_GIRDER:
	case CHAR_GIRDER_U1:
	case CHAR_GIRDER_U2:
	case CHAR_GIRDER_U3:
	case CHAR_GIRDER_U4:
	case CHAR_GIRDER_U5:
	case CHAR_GIRDER_U6:
	case CHAR_GIRDER_U7:
		return true;
	default:
		return false;
	}
		
}


/// Constructor

// Basic constructor for creating level layout based on given files, physics, and config.
/*DK_Level::DK_Level(char * levelFilepath, char * uiFilepath, Physics * physics, GameConfig * config) :
	Level(config->getRasterColumnsCount(), config->getRasterRowsCount(),
		config->getInternalRasterWidth(), config->getInternalRasterHeight(), physics)
{
	// 1. Get entity layout from file
	this->levelLayout = this->getLeveldata(levelFilepath, config->getRasterRowsCount(), config->getRasterColumnsCount());
	this->uiLayout = this->getLeveldata(uiFilepath, config->getRasterRowsCount(), config->getRasterColumnsCount());
	this->config = config;
	// 2. create entities in layered order by reading layout
	initEntities(levelLayout, uiLayout);
}*/

DK_Level::DK_Level(DK_Model* model, unsigned id) :
	Level(model->config->cols, model->config->rows,
		model->config->xCellSize, model->config->yCellSize,
		new Physics(model)
	)
{
	// 1. Retrieve Level[UI]layoutpaths from Config, then convert the file info into 2D char arrays
	this->model = model;
	this->levelLayout =	this->getLeveldata(model->config->getLevelLayoutPath(1), model->config->rows, model->config->cols);
	this->uiLayout = this->getLeveldata(model->config->getUILayoutPath(1), model->config->rows, model->config->cols);
	// 2. Initialize entity data for level and ui entities using 2D char arrays
	initEntities(this->levelLayout, this->uiLayout);
}


DK_Level::~DK_Level()
{
}

/// Methods for Game Action

// Main Function for changing entities.
void DK_Level::update() const
{
	auto request = model->requestHandler->getRequest();
	auto playerState = player->getPlayerState();
	bool velocityUp = (player->jumpVelocityRemaining() > 0);

	auto onGround = isOnGround(player);
	auto canMoveLeft = !isBlocked(player, Direction::LEFT);
	auto canMoveRight = !isBlocked(player, Direction::RIGHT);
	auto canClimbUp = canClimb(player, UP);
	auto canClimbDown = canClimb(player, DOWN);

	// 0. Calculate possible offset
	int xLeft = 0;
	if (canMoveLeft) xLeft = -1;
	int xRight = 0;
	if (canMoveLeft) xRight = 1;
	int yJumpDirection = -1;
	if (velocityUp) yJumpDirection = 1;

	// 1. add time tick to all entities
	// 2. check collision with barrels:
	// 3. Move player according to request, if possible
	switch (playerState)
	{
	case Entity_Jumpman::JUMP:
		this->player->update(yJumpDirection, 0, Entity_Jumpman::JUMP);
		break;
	case Entity_Jumpman::JUMP_LEFT:
		this->player->update(yJumpDirection, xLeft, Entity_Jumpman::JUMP);
		break;
	case Entity_Jumpman::JUMP_RIGHT:
		this->player->update(yJumpDirection, xLeft, Entity_Jumpman::JUMP);
		break;
	default: ;
	}
	

	switch (request)
	{
	case JUMP:
		if (onGround)
			this->player->update(1, 0, Entity_Jumpman::JUMP);
		break;
	case JUMP_LEFT:
		if (onGround)
			this->player->update(xLeft, 1, Entity_Jumpman::JUMP_LEFT);
		break;
	case JUMP_RIGHT:
		if (onGround)
			this->player->update(xRight, 1, Entity_Jumpman::JUMP_RIGHT);
		break;
	case MOVE_RIGHT:
		if (onGround) this->player->update(xRight, 0, Entity_Jumpman::MOVE_RIGHT);
		break;
	case MOVE_LEFT:
		if (onGround) this->player->update(xLeft, 0, Entity_Jumpman::MOVE_LEFT);
		break;
	case CLIMB_UP:
		if (canClimbUp) this->player->update(0, 1, Entity_Jumpman::CLIMB);
		break;
	case CLIMB_DOWN:
		if (canClimbDown) this->player->update(0, -1, Entity_Jumpman::CLIMB);
		break;
	default: ;
		// check for ladder intersecting [and ground below]
	}
	// 4. Adjust position after movement change.
	adjustPosition(player);
	//		check for bonus points
	// 5. Update DK
	// 6. Update barrels
	//	6.1 movement
	//	6.2 despawn
}

bool DK_Level::isOnGround(Entity* entity) const
{
	auto adjacentEntities = physics->checkAdjacency(static_cast<::PhysicalObject*>(entity), getPhysicalObjects(), Direction::DOWN, false);
	if (adjacentEntities != nullptr)
	{
		return true;
	}
	return false;
}

bool DK_Level::isBlocked(Entity* entity, Direction direction) const
{
	auto adjacentEntities = physics->checkAdjacency(static_cast<::PhysicalObject*>(entity), getPhysicalObjects(), direction, false);
	if (adjacentEntities != nullptr)
	{
		return true;
	}
	return false;
}

// Moves a given entity outside of a solid object (upwards) if an overlap has been detected.
// Note: If multiple objects overlap, moves it the upmost overlap upwards.
void DK_Level::adjustPosition(Entity* entity) const
{
	int maxOverlap = 0;
	auto adjacentEntities = physics->checkAdjacency(static_cast<::PhysicalObject*>(entity), getPhysicalObjects(), Direction::DOWN, true);
	if (adjacentEntities != nullptr)
	{
		for (auto iteratorB = adjacentEntities->begin(); iteratorB != adjacentEntities->end(); ++iteratorB)
		{
			auto obj = *iteratorB;
			auto distance = (physics->getRelativeYDistance(entity, obj));
			auto overlap = distance * -1;
			if (overlap > maxOverlap) maxOverlap = overlap;
			if (maxOverlap > 0) {
				entity->setPosition(entity->getPosX(), entity->getPosY() + maxOverlap);
			}
		}
	}
}

bool DK_Level::canClimb(Entity* entity, Direction direction) const
{
	const int distanceCentered = 0; // Distance from ladder to entity if they are both centered.
	auto adjacentEntities = physics->checkAdjacency(static_cast<::PhysicalObject*>(entity), getPhysicalObjects(), direction, true);
	if (adjacentEntities != nullptr)
	{
		for (auto iteratorB = adjacentEntities->begin(); iteratorB != adjacentEntities->end(); ++iteratorB)
		{
			auto obj = *iteratorB;
			// Check if object is a ladder
			if (static_cast<LadderEntity*>(obj) != nullptr) {
				auto distanceX = (physics->getRelativeXDistance(entity, obj));
				auto distanceY = (physics->getRelativeYDistance(entity, obj));
				int minOverlapY;
				// Ladders must touch player for climbing; but can just be adjacent for descending.
				direction == DOWN ? minOverlapY = 0 : minOverlapY = 1;
				if ((distanceX = distanceCentered) && (distanceY = -1 * minOverlapY)){
					return true;
				}
			}
		}
	}
	return false;
}
