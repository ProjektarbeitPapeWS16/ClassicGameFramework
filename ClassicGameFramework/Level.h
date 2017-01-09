﻿#pragma once
#include <string>
#include <vector>
#include "Grid.h"
class Physics;
class PhysicalObject;

class Level
{
	/* neu: über Grid Objekt
	int colCount;
	int columnCount;
	*/
	Grid* grid; // determines dimensions, and grid size
	Physics* physics;
	std::string* path; // to layout info file
public:
	Level(int colsGrid, int rowsGrid, int xTileSize, int yTileSize, std::string* path);

	std::vector<PhysicalObject>* getPhysicalObjects();
	char** getLeveldata(char* filepath, int rows, int cols);
};
