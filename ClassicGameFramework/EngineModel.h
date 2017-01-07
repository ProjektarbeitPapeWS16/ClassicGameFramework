#pragma once
#include "Session.h"
#include "Physics.h"
#include <set>
#include "Config.h"

class EngineModel
{

	Session session;
	Physics physics;

private:
	std::map<Key, std::function<void()>> *keyPressedListeners;
	std::map<Key, std::function<void()>> *keyReleasedListeners;

public:
	static bool gameloopShouldEnd;
	EngineModel(Session& session, Physics& physics);

	Session& getSession();
	
	// initializes the keyListeners and other stuff
	// is to be implemented by the game programmer
	virtual void initialization(); 

	virtual void nextIteration();

	std::map<Key, std::function<void()>> *getKeyPressedListeners();
	std::map<Key, std::function<void()>> *getKeyReleasedListeners();
	
};

