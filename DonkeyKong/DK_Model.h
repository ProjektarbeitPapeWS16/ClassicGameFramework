#pragma once
#include "EngineModel.h"
#include "DK_Config.h"
#include "DK_Level.h"
#include "Entity_Jumpman.h"
#include "Timer.h"

class DK_Config; //class GameConfig;
class DK_Session;

class DK_Model : public EngineModel
{
public:
	DK_Config* config; //sets grid, display size, title for game
	Timer* timer;
	/// External file path info
	//std::vector<const char*>* levelLayoutPaths; //array to filepaths that store level entity layout
	//std::vector<const char*>* uiLayoutPaths; //array filepaths with interface entity layout
	//const char* highscoreEntriesPath; // TODO: High Score data from previous games (only one file path)

	explicit DK_Model();
	explicit DK_Model(DK_Config* config); // std::vector<const char*>* levelLayoutPaths, std::vector<const char*>* uiLayoutPaths, const char* highscoreEntriesPath);
	~DK_Model() override;

	void initialization() override;
	void nextIteration() override;

	/// Events for keyListeners
	static void  keyUpPress();
	static void keyDownPress();
	static void keyLeftPress();
	static void keyRightPress();
	static void keySpacePress();   // Jump
	static void keyEscPress();	   // Exit

	// Used by:		Controller
	/*
	 *DK_Config* getConfig() const;
	const std::vector<char*>* getLevelLayoutPaths(int i) const;
	const std::vector<char*>* getUiLayoutPaths() const;
	const char* getHighscoreInfo() const;
*/
	// Get drawable entities from current session.
	// Used by: View
	std::vector<Entity*>* getDrawables() const; 
};