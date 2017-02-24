#pragma once
#include "EngineModel.h"
#include "Session.h"

#include "DK_Level.h"
#include "Entity_Jumpman.h"
#include "DK_Session.h"

class DK_Model : public EngineModel
{
	GameConfig* config;			//sets grid, display size, title for game
	const char** levelFilepaths;	//array to filepaths that store level entity layout
	const char* uiLayoutFilepaths;		//array filepaths with interface entity layout
	const char* highscoreInfo;	// TODO: High Score data from previous games
	DK_Session* session;		// Game session
public:
	DK_Model();
	DK_Model(DK_Session* session);
	DK_Model(DK_Session* session, GameConfig* config, char** levelLayouts);
	~DK_Model() override;

	void initialization() override;
	void nextIteration() override;
	// Events for keyListeners
	void static keyUpPress();
	void static keyDownPress();
	void static keyLeftPress();
	void static keyRightPress();
	void static keySpacePress();   // Jump
	void static keyEscPress(); // Exit

	// Getter for player entity
	// Used by:		Controller
	GameConfig* getConfig() const;
	const char* getLevelLayout(int i) const;
	const char* getUiLayout() const;
	const char* getHighscoreInfo() const;

	// Get drawable entities from current session.
	// Used by: View
	std::vector<Entity*>* getDrawables() const; 
};