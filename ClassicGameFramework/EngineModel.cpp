#include "EngineModel.h"
//#include <glfw3.h>
#define GLFW_PRESS 1
#define GLFW_RELEASE 0


void EngineModel::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode) const
{
	if (action == GLFW_PRESS)
	{
		if (keyPressedListeners->find(key) != keyPressedListeners->end())
		{
			std::function<void()>* fptr = keyPressedListeners->at(key);
			(*fptr)();
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (keyReleasedListeners->find(key) != keyReleasedListeners->end())
		{
			std::function<void()>* fptr = keyReleasedListeners->at(key);
			(*fptr)();
		}
	}
}

EngineModel::EngineModel(Session* session): session(session)
{
	keyReleasedListeners = new std::map<Key, std::function<void()>*>();
	keyPressedListeners = new std::map<Key, std::function<void()>*>();
}

std::map<Key, std::function<void()>*>* EngineModel::getKeyPressedListeners() const
{
	return keyPressedListeners;
}

std::map<Key, std::function<void()>*>* EngineModel::getKeyReleasedListeners() const
{
	return keyReleasedListeners;
}

Session* EngineModel::getSession()
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
}
