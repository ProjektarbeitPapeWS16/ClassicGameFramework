#pragma once
#include "Session.h"
#include "DK_Model.h"
#include "DK_Level.h"

// Class for managing a game session, for keeping track of things beyond level scope.
class DK_Session : public Session
{
private:
	const int INIT_BONUS = 2500;
	const int INIT_SCORE = 0;
	const int INIT_LIVES = 3;

	int bonus;			// Counts bonus points left. Resets with each level (or session).
	int highScore;		// Set by previous plays. Get from model, from external file.
	int* highScores;	// HighscoreList
	
	std::vector<char*>* levelLayoutPaths;	// Info for initializing levels
	std::vector<char*>* uiLayoutPaths;	// Info for UI entities

	DK_Level* level;	// Current level
	Physics* physics;  // Used for level. (Currently only one type --> always same physics)
public:
	DK_Session(std::vector<char*>* levelLayoutPaths, std::vector<char*>* uiLayoutPaths, int* highScores, GameConfig* config, Physics* physics);
	DK_Session();

	// Event handlers
	void doEvent_Death();		// do events on death; including score and lvl reset
	void doEvent_nextLevel();	// prepare next level if player has beaten current one
	void increaseScore(int points);	// add points to score when player acquired points
	void doEvent_TimePassed(); // decrease bonus after certain periods
	void doEvent_Reset();	   // called after a session has ended.

	// Getters
	DK_Level* getLevel();
	//int getScore();
	//int getLives();
};