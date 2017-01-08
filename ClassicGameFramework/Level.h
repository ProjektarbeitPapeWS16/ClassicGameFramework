#pragma once
#include <string>
class Physics;

class Level
{
	int rowCount;
	int columnCount;
	std::string *path;
	// TODO: lifes? siehe Klassendiagramm
public:
	Level(int row_count, int column_count, std::string *path);

	int getRowCount();
	int getColumnCount();
	std::string *getPath();
};
