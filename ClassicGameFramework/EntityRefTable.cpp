#include "EntityRefTable.h"
#include <iterator>

EntityRefTable::EntityRefTable()
{
}

EntityTypeStats* EntityRefTable::getEntityTypeStats(char c)
{
	std::map<char, EntityTypeStats>* map = this->entityTypes;
	std::map<char, EntityTypeStats>::iterator it;
	for (it=map->begin(); it!=map->end(); it++) // iterate using keys
	{
		return &it->second; // Return map value; i.e. the EntityTypeStruct
	}
	return nullptr;	// Else return nullpointer? TODO: Try/catch here.
}

void EntityRefTable::addEntityType(EntityTypeStats entityTypeStats)
{
	char typeSymbol = entityTypeStats.typeSymbol;
	// Insert entityType to map, using its TypeSymbol as key.
	// (Only adds type if an entity with that typesymbol is yet not part of the map)
	this->entityTypes[typeSymbol].insert_or_assign(typeSymbol, entityTypeStats);
}

Entity * EntityRefTable::getEntity(char c, int xPos, int yPos)
{
	return nullptr; // TODO
}

// for use with Grid
Entity * EntityRefTable::getEntity(char c, Position pos)
{
	return nullptr;
}

EntityRefTable::~EntityRefTable()
{
}
