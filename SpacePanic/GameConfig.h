#pragma once

class GameConfig
{
	
	//Attributes
	int internal_width;
	int internal_height;
	int external_factor;
	int raster_width;
	int raster_height;
	const char* title;
public:

	//Constructors
	//GameConfig();
	GameConfig(const char* title, int internal_width, int internal_height, int external_factor, int raster_width, int raster_height);

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
	const char* getTitle() const;
};
