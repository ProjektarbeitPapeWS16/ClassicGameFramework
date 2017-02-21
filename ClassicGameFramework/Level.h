#pragma once
#include <vector>
#include "Grid.h"
//class Physics;
class PhysicalObject;
class Entity;
class Physics;

class Level
{
	/* neu: über Grid Objekt
	int colCount;
	int columnCount;
	*/
	Grid* grid; // determines dimensions, and grid size
	Physics* physics;
protected:
	std::vector<Entity*>* entities;
public:
	virtual ~Level();

	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize);
	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, Physics* physics);
	Physics* getPhysics() const;
	void setPhysics(Physics* physics);
	std::vector<Entity*>* getEntities() const;
	void setEntities(std::vector<Entity*>* entities);
	std::vector<PhysicalObject*>* getPhysicalObjects() const;
	char** getLeveldata(const char* filepath, unsigned rows, unsigned cols) const;
};
