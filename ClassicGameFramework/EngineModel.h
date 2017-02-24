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

// Model of MVC paradigm; for managing a game's session through player inputs
class EngineModel
{
private:
	static EngineModel* instance;

	// Listener
	// Monitors player input; to be used for computing events.
	std::map<Key, std::function<void()>*>* keyPressedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyReleasedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyDownListeners = nullptr;

	std::vector<Key>* keyDownKeys = nullptr;

	
protected:
	Session* session; // contains physics, level, and its entities
	virtual void handleCollisions(); // defines game events for game's respective entity types

public:
	bool shouldClose = false;

	// Empty constructor for creating model with basic physics, session and level with default dimensions.
	EngineModel(); 

	// Standard constructor for creating model with custom physics and session.
	EngineModel(Physics* physics, Session* session);

	// Standard constructor for creating model with custom physics, session, and level.
	EngineModel(Physics* physics, Session* session, Level* level);

	// Destructor
	virtual ~EngineModel()
	{
	}

	// listeners [registered with key] are being called.
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

	// Getter for: Character keys initially pressed [considering modifiers including delays/repeat]
	std::map<Key, std::function<void()>*>* getKeyPressedListeners() const;
	// Getter for: Keys released
	std::map<Key, std::function<void()>*>* getKeyReleasedListeners() const;
	// Getter for: Keys [still] pressed in the current cycle [considering modifiers] (called for repeat)
	std::map<Key, std::function<void()>*>* getKeyDownListeners() const;
	std::vector<Key>* getKeyDownKeys() const;

	// TODO make an Interface
};
