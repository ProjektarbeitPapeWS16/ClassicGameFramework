#include "EngineModel.h"
#include <glfw3.h>

EngineModel::EngineModel(Session& session, Physics& physics): session(session),
                                                              physics(physics)
{
}

Session& EngineModel::getSession()
{
	// TODO
	return this->session;
}

void EngineModel::nextIteration(std::set<Key> keys)
{
	// TODO
	if(keys.find(GLFW_KEY_ESCAPE) != keys.end())
	{
		gameloopShouldEnd = true;
	}
}
