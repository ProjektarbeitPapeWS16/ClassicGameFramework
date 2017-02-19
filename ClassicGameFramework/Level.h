#pragma once
#include <string>
#include <vector>
#include "Grid.h"
//class Physics;
class PhysicalObject;
class Entity;

class Level
{
	/* neu: über Grid Objekt
	int colCount;
	int columnCount;
	*/
	Grid* grid; // determines dimensions, and grid size
	//Physics* physics;
	std::string* path; // to layout info file
protected:
	std::vector<Entity*>* entities;
public:
	virtual ~Level()
	{
	}

	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path);

	//Physics* getPhysics();
	std::vector<Entity*>* getEntities() const;
	void setEntities(std::vector<Entity*>* entities);
	std::vector<PhysicalObject*>* getPhysicalObjects() const;
	char** getLeveldata(char* filepath, unsigned int rows, unsigned int cols) const;
};
