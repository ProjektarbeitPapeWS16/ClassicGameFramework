#pragma once
#include <string>
#include <vector>
class Physics;
class PhysicalObject;

class Level
{
	int rowCount;
	int columnCount;
	const std::string *path;
	Physics *physics;
	// TODO: lifes? siehe Klassendiagramm
public:
	Level(int row_count, int column_count, const std::string *path, Physics *physics);

	int getRowCount();
	int getColumnCount();
	const std::string *getPath();

	std::vector<PhysicalObject> * getPhysicalObjects();
};
