#include "EngineModel.h"
//#include <glfw3.h>

bool EngineModel::gameloopShouldEnd = false;


void EngineModel::addKeyPressedListener(int i, void(* fptr)())
{
	keyPressedListeners.insert_or_assign(i, &fptr);
}

void EngineModel::addKeyReleasedListener(int i, void(*fptr)())
{
	keyReleasedListeners.insert_or_assign(i, &fptr);
}

EngineModel::EngineModel(Session& session, Physics& physics): session(session),
                                                              physics(physics)
{
}

Session& EngineModel::getSession()
{
	// TODO
	return this->session;
}

void EngineModel::nextIteration()
{
	// TODO

	/*
	if(keys.find(GLFW_KEY_ESCAPE) != keys.end())
	{
		gameloopShouldEnd = true;
	}*/
}
