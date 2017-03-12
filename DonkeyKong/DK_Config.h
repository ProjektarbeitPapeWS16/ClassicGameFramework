#pragma once
#include "Config.h"
#include <vector>
#include "Grid.h"

// General Information for initialization
namespace dk_Config_general
{
	static const char* DK_TITLE = "DONKEY KONG";	// Game Title
												
	static const unsigned int DK_CELLSIZE = 8;		// Pixels used for grid cell subdivision in a level (for 8x8px tiles)
	static const unsigned int DK_ROWCOUNT = 32;		// Amount of horizontal grid subdivisions
	static const unsigned int DK_COLCOUNT = 28;		// Amount of vertical grid subdivisions
	static const unsigned int DK_WIDTH = 224;		// Window width --	28 x 8px tiles
	static const unsigned int DK_HEIGHT = 256;		// Window height --	32 x 8px tiles
	static const Grid* DK_GRID = new Grid(DK_COLCOUNT, DK_ROWCOUNT, DK_CELLSIZE, DK_CELLSIZE);	// Information for grid dimensions for a level

	// Information for loading levels via external files
	static const unsigned int DK_LEVELCOUNT = 1;		// Amount of levels in the game (currently only 1)
	static const unsigned int DK_UICOUNT = 1;			// Amount of UI types in the game

	static const char* DK_LEVELLAYOUTPATH_1 = "levels\\level_25m.txt"; // Relative PJ path to first level						
	static const char* DK_LEVELLAYOUTPATH_TEST = "levels\\level_test.txt"; // Relative PJ path to first level						
	static const char* DK_UILAYOUTPATH_1 = "levels\\level_ui.txt"; // Relative PJ path to ui layout for first level

	static const std::array<const char*, DK_LEVELCOUNT>* DK_LEVELLAYOUTPATHS;	// pre-defined list of all paths to file for layout of n-th level
	static const std::array<const char*, DK_UICOUNT>* DK_UILAYOUTPATHS;		// pre-defined list of all paths to file for layout of n-th ui	

	// Highscore Info
	// static const char* DK_HIGHSCOREPATH = "..\\highscores.txt";	// TODO: Create file
}


// Used to retrieve constant values that are needed for consistency.
class DK_Config : public Config
{
public:
	static const char* title;

	static const unsigned int width = dk_Config_general::DK_WIDTH;			// Window width
	static const unsigned int height = dk_Config_general::DK_HEIGHT;		// Window height
	static const unsigned int cols = dk_Config_general::DK_COLCOUNT;
	static const unsigned int rows = dk_Config_general::DK_ROWCOUNT;
	static const unsigned int xCellSize = dk_Config_general::DK_CELLSIZE;		
	static const unsigned int yCellSize = dk_Config_general::DK_CELLSIZE;		
	static const Grid* grid;
	// Grid* myGrid = new Grid(10, 10, 10, 10);
	static const std::array<const char*, dk_Config_general::DK_LEVELCOUNT>* levelLayoutPaths;	// pre-defined list of all paths to file for layout of n-th level
	static const std::array<const char*, dk_Config_general::DK_UICOUNT>* uiLayoutPaths;		// pre-defined list of all paths to file for layout of n-th ui
	
	static const char* levelLayoutPath1;
	static const char* uilLayoutPath1;

	//Constructor
	explicit DK_Config(){};

	// Functions
	
	static const char* getTitle();
	static const char* getLevelLayoutPath(unsigned int levelID);
	static const char* getUILayoutPath(unsigned int uiID);
};

// init file path vectors
//std::array<const char*, dk_Config_general::DK_LEVELCOUNT>* DK_Config::levelLayoutPaths[1] = new std::array<const char*, dk_Config_general::DK_LEVELCOUNT>; //dk_Config_general::DK_LEVELLAYOUTPATH_1;

// const std::array<const char*, dk_Config_general::DK_LEVELCOUNT>* DK_Config::levelLayoutPaths = dk_Config_general::DK_LEVELLAYOUTPATHS;
//const std::array<const char*, dk_Config_general::DK_LEVELCOUNT>* DK_Config::levelLayoutPaths = { "a", "b" };
//DK_Config::levelLayoutPaths

//const std::array<const char*, dk_Config_general::DK_UICOUNT>* DK_Config::uiLayoutPaths = std::array<dk_Config_general::DK_UILAYOUTPATH_1, dk_Config_general::DK_LEVELLAYOUTPATH_1>; //DK_UILAYOUTPATHS;
// DK_Config::uiLayoutPaths->push_back(DK_UILAYOUTPATH_1);

