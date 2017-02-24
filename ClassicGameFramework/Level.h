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
protected:
	char** levelLayout; // pointer to 2D array of characters representing entity location
	Grid* grid; // determines dimensions, and grid size
	Physics* physics;
	std::vector<Entity*>* entities;
public:
	virtual ~Level();

	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize);
	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, Physics* physics);

	Grid* getGrid() const;
	char** getLevelLayout() const;

	Physics* getPhysics() const;
	void setPhysics(Physics* physics);
	virtual std::vector<Entity*>* getEntities() const;
	void setEntities(std::vector<Entity*>* entities);
	
	std::vector<PhysicalObject*>* getPhysicalObjects() const;

	char** getLeveldata(const char* filepath, unsigned int rows, unsigned int cols) const;
};
