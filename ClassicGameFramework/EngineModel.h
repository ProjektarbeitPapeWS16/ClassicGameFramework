#pragma once

#include <map>
#include <functional>
#include <vector>
class Session;
typedef int Key;
struct GLFWwindow;

class EngineModel
{
	Session* session = nullptr;

	// Listener
	std::map<Key, std::function<void()>*>* keyPressedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyReleasedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyDownListeners = nullptr;

	std::vector<Key>* keyDownKeys = nullptr;
	
	static EngineModel* instance;

public:
	// Konstruktor
	//EngineModel(Session* session); // deprecated
	EngineModel();

	// Destruktor
	virtual ~EngineModel()
	{
	}

	// listeners registered with key are being called.
	void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode) const;
	
	// TODO description
	void key_down();
	

	// initializes the keyListeners and other stuff
	// (override)
	virtual void initialization();

	// calculates the next Iteration
	// (override)
	virtual void nextIteration();

	// getter
	static EngineModel* getInstance();
	Session* getSession();
	std::map<Key, std::function<void()>*>* getKeyPressedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyReleasedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyDownListeners() const;
	std::vector<Key>* getKeyDownKeys() const;

	// TODO make an Interface
};
