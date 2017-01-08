#include "Level.h"
#include "Physics.h"

Level::Level(int row_count, int column_count, std::string * path) : rowCount(row_count),
	columnCount(column_count),
	path(path)
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

std::string * Level::getPath() 
{
	return path;
}

