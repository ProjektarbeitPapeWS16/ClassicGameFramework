#include "GameConfig.h"

//Chr: Copied from SpacePanic PJ for Text.CPP
GameConfig::GameConfig() : internal_width(192), internal_height(256), external_factor(2), raster_width(8), raster_height(8)
{
}

GameConfig::GameConfig(int internal_width, int internal_height, int external_factor, int raster_width, int raster_height) : internal_width(internal_width),
internal_height(internal_height),
external_factor(external_factor),
raster_width(raster_width),
raster_height(raster_height)
{
}

GameConfig::~GameConfig()
{
}

int GameConfig::getInternalWidth() const
{
	return internal_width;
}

int GameConfig::getInternalHeight() const
{
	return internal_height;
}

int GameConfig::getExternalFactor() const
{
	return external_factor;
}

int GameConfig::getInternalRasterWidth() const
{
	return raster_width;
}

int GameConfig::getInternalRasterHeight() const
{
	return raster_height;
}


int GameConfig::getWidth() const
{
	return applyFactor(internal_width);
}

int GameConfig::getHeight() const
{
	return applyFactor(internal_height);
}

int GameConfig::getX(int x) const
{
	return applyFactor(x);
}

int GameConfig::getY(int y) const
{
	return applyFactor(y);
}

int GameConfig::getRasterWidth() const
{
	return applyFactor(raster_width);
}

int GameConfig::getRasterHeight() const
{
	return applyFactor(raster_height);
}

int GameConfig::getRasterColumnsCount() const
{
	return internal_width / raster_width;
}

int GameConfig::getRasterRowsCount() const
{
	return internal_height / raster_height;
}

int GameConfig::applyFactor(int someXOrYValue) const
{
	return someXOrYValue * external_factor;
}
