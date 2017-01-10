#pragma once
#include <map>
#include "../SpacePanic/EnemyEntity.h"

const int DEFAULT_SIZE = 16; // common sprite size for arcade games (e.g. Pacman Ghosts)
const int DEFAULT_SPEED = 8; // fraction of common grid cell size
// const std::string DEFAULT_IMAGE = "../images/entity_TypeDefault.bmp"; 
const char DEFAULT_TYPESYMBOL = 'x'; // default entity character (usually wall)

// Provides information for creating an entity of a specific type
// Can be created to define all entity type attributes for a respective game 
// TODO: Used by: EngineModel
struct EntityTypeStats
{
	// 1. Information for creating a respective Entity object
	bool solid = true;		// True, if it is an obstacle (can't be passed). Used by Physics
	bool movable = false;	// True, if entity is moved via player inputs (not:position can change (through physics))
	int movementSpeed = DEFAULT_SPEED;
	int animationSpeed = DEFAULT_SPEED;
	std::string* imagePath; // filepath for bitmap with sprites for texture (and animation)
	int width = DEFAULT_SIZE;
	int height = DEFAULT_SIZE;
	//TODO: AI behavior

	// 2. Information for deriving type from given levelinfo.txt; and more?
	std::string name;	//Entity type name
	char typeSymbol = DEFAULT_TYPESYMBOL;
};

// Class that contains a reference table. Uses:
// 1. listing all entity types for a particular game
//	  a) Provide type for determining respective behavior:
//		 {player characters, enemy types, obstacle types, ground types}
//	  b) Provide name of respective bitmap file to use as texture for renderer
//    c) Provide respective character that represents it in a levelinfo.txt file
// TODO: Used by: EngineModel
class EntityRefTable
{
	int typeCount; // Amount of entity types in the game
	
	// List containing the information for all entity types available; TypeSymbols serve as keys.
	std::map<char, EntityTypeStats>* entityTypes; 
public:
	EntityRefTable();

	//TODO: (optional) path to textfile containing all information about entities
	// --> make Entity edits easier by changing stats on external file
	// that lists the attributes and bitmap file paths, seperated by comma
	// example:
	// alternative: just use to map character to entity class 
	// Name, Image, Size, Speed, isSolid, isPlayer, 
//	EntityRefTable(std::string* entityinfopath);

	// Getter for entity type based on character used for representation in text files.
	// If none could be found, returns nullpointer.
	EntityTypeStats* getEntityTypeStats(char typeSymbol);

	// Method for filling class with entity type information.
	void addEntityType(EntityTypeStats entityTypeStats);
	// Factory:
	// todo: provide Grid parameter for centering?
	Entity* getEntity(char c, int xPos, int yPos);
	Entity* getEntity(char c, Position pos);
	~EntityRefTable();
};
