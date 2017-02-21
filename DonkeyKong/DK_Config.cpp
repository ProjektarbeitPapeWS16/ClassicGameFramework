// #include "stdafx.h"
#include "DK_Config.h"

DK_Config::DK_Config() : internal_width(192), internal_height(256), external_factor(2), raster_width(8), raster_height(8)
{
}

DK_Config::DK_Config(int internal_width, int internal_height, int external_factor, int raster_width, int raster_height) : internal_width(internal_width),
internal_height(internal_height),
external_factor(external_factor),
raster_width(raster_width),
raster_height(raster_height)
{
}

int DK_Config::getInternalWidth() const
{
	return internal_width;
}

int DK_Config::getInternalHeight() const
{
	return internal_height;
}

int DK_Config::getExternalFactor() const
{
	return external_factor;
}

int DK_Config::getInternalRasterWidth() const
{
	return raster_width;
}

int DK_Config::getInternalRasterHeight() const
{
	return raster_height;
}


int DK_Config::getWidth() const
{
	return applyFactor(internal_width);
}

int DK_Config::getHeight() const
{
	return applyFactor(internal_height);
}

int DK_Config::getX(int x) const
{
	return applyFactor(x);
}

int DK_Config::getY(int y) const
{
	return applyFactor(y);
}

int DK_Config::getRasterWidth() const
{
	return applyFactor(raster_width);
}

int DK_Config::getRasterHeight() const
{
	return applyFactor(raster_height);
}

int DK_Config::getRasterColumnsCount() const
{
	return internal_width / raster_width;
}

int DK_Config::getRasterRowsCount() const
{
	return internal_height / raster_height;
}

int DK_Config::applyFactor(int someXOrYValue) const
{
	return someXOrYValue * external_factor;
}
