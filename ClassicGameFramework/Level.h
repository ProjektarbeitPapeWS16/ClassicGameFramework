#pragma once
#include <string>
class Physics;

class Level
{
	int rowCount;
	int columnCount;
	const std::string *path;
	Physics *physics;
public:
	Level(int row_count, int column_count, const std::string *path, Physics *physics);

	int getRowCount();
	int getColumnCount();
	const std::string *getPath();
};
