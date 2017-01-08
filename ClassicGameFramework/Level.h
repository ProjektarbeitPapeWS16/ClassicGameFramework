#pragma once
#include <string>
#include <vector>
class Physics;
class PhysicalObject;

class Level
{
	int rowCount;
	int columnCount;
	Physics *physics;
	std::string* path;
public:
	Level(int row_count, int column_count, std::string* path);

	int getRowCount();
	int getColumnCount();
	std::string* getPath();

	std::vector<PhysicalObject>* getPhysicalObjects();
};
