#include "EngineModel.h"
#include <glfw3.h>

bool EngineModel::gameloopShouldEnd = false;

EngineModel::EngineModel(Session& session, Physics& physics): session(session),
                                                              physics(physics)
{
	
}

std::map<int, std::function<void()>> *EngineModel::getKeyPressedListeners()
{
	return keyPressedListeners;
}

std::map<int, std::function<void()>> *EngineModel::getKeyReleasedListeners()
{
	return keyReleasedListeners;
}

Session& EngineModel::getSession()
{
	// TODO
	return this->session;
}

void EngineModel::initialization()
{
}

void EngineModel::nextIteration()
{
	// TODO
	if (false)
	{
		gameloopShouldEnd = true;
	}
}
