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
	//TODO: Add EntityRefTable? (to specify entity types out of initialization method)

	std::map<Key, std::function<void()>*>* keyPressedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyReleasedListeners = nullptr;
	std::map<Key, std::function<void()>*>* keyDownListeners = nullptr;
	std::vector<Key>* keyDownKeys = nullptr;
	static EngineModel* instance;

public:
	static EngineModel* getInstance();

	virtual ~EngineModel()
	{
	}

	void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode) const;
	void key_down();

	EngineModel(Session* session);

	Session* getSession();

	// initializes the keyListeners and other stuff
	// is to be implemented by the game programmer
	virtual void initialization();

	virtual void nextIteration();

	std::map<Key, std::function<void()>*>* getKeyPressedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyReleasedListeners() const;
	std::map<Key, std::function<void()>*>* getKeyDownListeners() const;
	std::vector<Key>* getKeyDownKeys() const;
};
