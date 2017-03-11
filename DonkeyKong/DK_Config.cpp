#include "DK_Config.h"
#include "Level.h"
// Unused. 
DK_Config::DK_Config()
{
	// Unused; only used for static access
}

const char * DK_Config::getTitle() const
{
	return this->title;
}

const char * DK_Config::getTitle()
{
	return title;
}

// Returns the filepath for a given level number.
static char * DK_Config::getLevelLayoutPath(unsigned int levelNr)
{
	return this->levelLayoutPaths->at(levelNr);
}

static char * DK_Config::getUILayoutPath(unsigned int uiNr)
{
	return DK_Config::uiLayoutPaths->at(uiNr);
}
