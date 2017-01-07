#include "Level.h"
#include "Physics.h"

Level::Level(int row_count, int column_count, const std::string * path, Physics * physics) : rowCount(row_count),
	columnCount(column_count),
	path(path),
	physics(physics)
{
}

int Level::getRowCount()
{
	return rowCount;
}

int Level::getColumnCount() 
{
	return columnCount;
}

const std::string * Level::getPath() 
{
	return path;
}

