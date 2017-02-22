#include "EngineModel.h"
//#include <glfw3.h>
#include "EngineView.h"
#include "Renderer.h"
#include "Session.h"
//#include "Level.h"
#include "Entity.h"
#include "Physics.h"
#include "Level.h"
#define GLFW_PRESS 1
#define GLFW_RELEASE 0

EngineModel *EngineModel::instance = nullptr;

EngineModel::EngineModel() : EngineModel(new Physics(), new Session(), new Level(100, 100, 1, 1))
{
}

EngineModel::EngineModel(Physics* physics, Session* session, Level* level) :
imageService(new ImageService()),
session(session)
{
	EngineModel::instance = this;
	if(session != nullptr && level != nullptr)
	{
		if(physics != nullptr) {
			level->setPhysics(physics);
		}

		session->setLevel(level);
	}
	
	//entities = new std::vector<Entity*>();
	
	keyReleasedListeners = new std::map<Key, std::function<void()>*>();
	keyPressedListeners = new std::map<Key, std::function<void()>*>();
	keyDownListeners = new std::map<Key, std::function<void()>*>();
	keyDownKeys = new std::vector<Key>();
}

ImageService* EngineModel::getImageService() const
{
	return imageService;
}

EngineModel::~EngineModel()
{
	delete session;
	delete imageService;
	delete keyPressedListeners;
	delete keyReleasedListeners;
	delete keyDownListeners;
	delete keyDownKeys;
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

void EngineModel::key_down(GLFWwindow* window) const
{
	for(unsigned int i = 0; i < keyDownKeys->size(); i++)
	{
		auto key = keyDownKeys->at(i);
		if(glfwGetKey(window, key) == GLFW_PRESS && keyDownListeners->find(key) != keyDownListeners->end())
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
	return session->getLevel();
}

Physics* EngineModel::getPhysics()
{
	return session->getLevel()->getPhysics();
}

// setter
void EngineModel::setSession(Session* session)
{
	if(this->session != nullptr)
	{
		delete this->session;
	}
	this->session = session;
}

void EngineModel::setLevel(Level* level)
{
	this->session->setLevel(level);
}

void EngineModel::setPhysics(Physics* physics)
{
	session->getLevel()->setPhysics(physics);
}

std::vector<Entity*>* EngineModel::getEntities()
{
	return session->getLevel()->getEntities();
}
