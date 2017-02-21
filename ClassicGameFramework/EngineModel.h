#pragma once

#include <map>
#include <functional>
#include <vector>
class Session;
class Level;
class Entity;
class Physics;

typedef int Key;
struct GLFWwindow;

class EngineModel
{
private:
	static EngineModel* instance;

	// Listener
	std::map<Key, std::function<void()>*>* keyPressedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyReleasedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyDownListeners = nullptr;

	std::vector<Key>* keyDownKeys = nullptr;

	
protected:
	Session* session;
	//Level* level;
	//Physics* physics;
	//std::vector<Entity*>* entities;

	virtual void handleCollisions();

	
public:
	bool shouldClose = false;
	// Konstruktor
	EngineModel();
	EngineModel(Physics* physics, Session* session, Level* level);
	// Destruktor
	virtual ~EngineModel()
	{
	}

	// listeners registered with key are being called.
	void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode) const;
	
	// TODO description
	void key_down(GLFWwindow* window) const;
	

	// initializes the keyListeners and other stuff
	virtual void initialization();

	// calculates the next Iteration
	virtual void nextIteration();

	// getter
	static EngineModel* getInstance();
	Session* getSession();
	Level* getLevel();
	Physics* getPhysics();
	void setSession(Session* session);
	void setLevel(Level* level);
	void setPhysics(Physics* physics);

	virtual std::vector<Entity*>* getEntities();
	std::map<Key, std::function<void()>*>* getKeyPressedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyReleasedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyDownListeners() const;
	std::vector<Key>* getKeyDownKeys() const;

	// TODO make an Interface
};
