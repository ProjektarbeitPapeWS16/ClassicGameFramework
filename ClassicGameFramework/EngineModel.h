#pragma once
#include "Session.h"
#include "Physics.h"
//#include <set>

class EngineModel
{
protected:
	Session session;
	Physics physics;
	std::map<int, void(*)()> keyPressedListeners;
	std::map<int, void(*)()> keyReleasedListeners;
public:
	virtual ~EngineModel()
	{
	}

	void addKeyPressedListener(int i, void(* fptr)());
	void addKeyReleasedListener(int i, void (*fptr)());
	static bool gameloopShouldEnd;
	EngineModel(Session& session, Physics& physics);

	Session& getSession();
	virtual void nextIteration();
};

