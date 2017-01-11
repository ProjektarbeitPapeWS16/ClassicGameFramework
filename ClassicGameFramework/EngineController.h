#pragma once

class EngineView;
class EngineModel;
typedef int Key;
struct GLFWwindow;

class EngineController
{
protected:
	EngineView* view = nullptr;
	EngineModel* model = nullptr;

	static EngineController* instance;
public:
	double timeElapsed = 0.0;
	double lastTime = 0.0;

	static EngineController* getInstance();

	static EngineModel* staticModel;
	static void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode);

	EngineController(EngineView* view, EngineModel* model);
	virtual void cycle() = 0;
	void gameLoop();
	void closeWindow() const;
	virtual ~EngineController();
};
