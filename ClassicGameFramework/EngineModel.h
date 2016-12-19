#pragma once
#include "Session.h"
#include "Physics.h"
#include <set>

class EngineModel
{
protected:
	Session session;
	Physics physics;
	
public:
	static bool gameloopShouldEnd;
	EngineModel(Session& session, Physics& physics);

	Session& getSession();
	virtual void nextIteration(std::set<Key> keys);
};

