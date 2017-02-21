#pragma once

/*
 * Class for setting window and grid size.
 * USED BY: DK_Controller, DK_Model
 */
class DK_Config
{

	//Attributes
	int internal_width;
	int internal_height;
	int external_factor;
	int raster_width;
	int raster_height;

public:

	//Constructors
	DK_Config();
	DK_Config(int internal_width, int internal_height, int external_factor, int raster_width, int raster_height);

	//Getters
	int getInternalWidth() const;
	int getInternalHeight() const;
	int getExternalFactor() const;
	int getInternalRasterWidth() const;
	int getInternalRasterHeight() const;
	int getWidth() const;
	int getHeight() const;
	int getX(int x) const;
	int getY(int y) const;
	int getRasterWidth() const;
	int getRasterHeight() const;
	int getRasterColumnsCount() const;
	int getRasterRowsCount() const;

	// Functions
	int applyFactor(int intX) const;
};
