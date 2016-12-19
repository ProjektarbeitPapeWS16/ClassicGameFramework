#pragma once
#include <string>
#include "Physics.h"

class Level
{
	int rowCount;
	int columnCount;
	std::string path;
	Physics physics;
	// TODO: lifes? siehe Klassendiagramm
public:
	Level(int row_count, int column_count, const std::string& path, const Physics& physics)
		: rowCount(row_count),
		  columnCount(column_count),
		  path(path),
		  physics(physics)
	{
	}

	int getRowCount();
	int getColumnCount();
	std::string getPath();
};
