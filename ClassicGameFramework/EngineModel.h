#pragma once

#include <map>
#include <functional>
class Session;
typedef int Key;
struct GLFWwindow;

class EngineModel
{
	Session* session = nullptr;

	std::map<Key, std::function<void()>*>* keyPressedListeners = nullptr;// new std::map<Key, std::function<void()>>();
	std::map<Key, std::function<void()>*>* keyReleasedListeners = nullptr; // new std::map<Key, std::function<void()>>();

public:
	virtual ~EngineModel()
	{
	}

	void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode) const;
	EngineModel(Session* session);

	Session* getSession();

	// initializes the keyListeners and other stuff
	// is to be implemented by the game programmer
	virtual void initialization();

	virtual void nextIteration();

	std::map<Key, std::function<void()>*>* getKeyPressedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyReleasedListeners() const;
};
