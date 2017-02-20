#include "EngineModel.h"
//#include <glfw3.h>
#include "EngineView.h"
#include "Renderer.h"
#include "Session.h"
#include "Level.h"
#include "Entity.h"
#include "Physics.h"
#define GLFW_PRESS 1
#define GLFW_RELEASE 0

EngineModel *EngineModel::instance = nullptr;

EngineModel::EngineModel()
{
	session = new Session();
	level = new Level(100, 100, 1, 1);
	entities = new std::vector<Entity*>();
	physic = new Physics();

	EngineModel::instance = this;
	keyReleasedListeners = new std::map<Key, std::function<void()>*>();
	keyPressedListeners = new std::map<Key, std::function<void()>*>();
	keyDownListeners = new std::map<Key, std::function<void()>*>();
	keyDownKeys = new std::vector<Key>();
}

EngineModel* EngineModel::getInstance()
{
	return instance;
}

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

void EngineModel::key_down()
{
	for(unsigned int i = 0; i < keyDownKeys->size(); i++)
	{
		Key key = keyDownKeys->at(i);
		if(glfwGetKey(EngineView::getInstance()->renderer->window, key) == GLFW_PRESS && keyDownListeners->find(key) != keyDownListeners->end())
		{
			std::function<void()>* fptr = keyDownListeners->at(key);
			(*fptr)();
		}
	}
}



std::map<Key, std::function<void()>*>* EngineModel::getKeyPressedListeners() const
{
	return keyPressedListeners;
}

std::map<Key, std::function<void()>*>* EngineModel::getKeyReleasedListeners() const
{
	return keyReleasedListeners;
}

std::map<Key, std::function<void()>*>* EngineModel::getKeyDownListeners() const
{
	return keyDownListeners;
}

std::vector<Key>* EngineModel::getKeyDownKeys() const
{
	return keyDownKeys;
}

void EngineModel::initialization()
{
}

void EngineModel::nextIteration()
{
	handleCollisions();
	// TODO
}


void EngineModel::handleCollisions()
{
	// TODO
}


// getter
Session* EngineModel::getSession() 
{	
	return session;	
}

Level* EngineModel::getLevel() 
{	
	return level;	
}

std::vector<Entity*>* EngineModel::getEntities()
{
	return entities;
}