#pragma once

class EngineView;
class EngineModel;
typedef int Key;
struct GLFWwindow;

// Controller of MVC paradigm; controls interaction between a given view and model through keyboard inputs and a timer.
class EngineController
{
protected:
	EngineView* view = nullptr;
	EngineModel* model = nullptr;

	//static EngineController* instance;
public:
	double timeElapsed = 0.0;	// For time polling.
	double lastTime = 0.0;

	//static EngineController* getInstance();
	//static EngineModel* staticModel;

	// Handles key inputs received from the player
	static void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode);

	// Constructor
	EngineController(EngineView* view, EngineModel* model); 

	// Destructor
	virtual ~EngineController();	

	// Actions to repeat for each cycle
	// Used by: gameLoop
	virtual void cycle() = 0;	

	// Infinite loop to iterate while game is running.
	void gameLoop();

	//void closeWindow() const;
	
};
