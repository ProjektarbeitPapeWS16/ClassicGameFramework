#pragma once
#include "GameConfig.h"
/*
 * Class for setting window and grid size.
 * USED BY: DK_Controller, DK_Model
 */
class DK_Config : public GameConfig
{
public:
	//TODO: Spritesheet class?
	DK_Config(int internal_width, int internal_height, int external_factor, int raster_width, int raster_height);

	//~GameConfig() override;
};