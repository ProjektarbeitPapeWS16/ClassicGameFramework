#include "DK_Config.h"

// Unused. 
/*
 *DK_Config::DK_Config()
{
	// Unused; only used for static access
}
*/

// Initialize static members:
//char const* DK_Config::title = dk_Config_general::DK_TITLE;

const char* DK_Config::title = dk_Config_general::DK_TITLE;
Grid const* DK_Config::grid = dk_Config_general::DK_GRID;

const char* DK_Config::levelLayoutPath1 = dk_Config_general::DK_LEVELLAYOUTPATH_1; // HACK (get around array const list)
const char* DK_Config::uilLayoutPath1 = dk_Config_general::DK_UILAYOUTPATH_1;	   // HACK


const char * DK_Config::getTitle()
{
	return title;
}

// Returns the filepath for a given level number.
const char* DK_Config::getLevelLayoutPath(unsigned int levelNr)
{
	return levelLayoutPath1;// levelLayoutPaths->at(levelNr);
}

const char* DK_Config::getUILayoutPath(unsigned int uiNr)
{
	return uilLayoutPath1;
}
