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
public:
	static EngineModel* staticModel;
	static void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode);

	EngineController(EngineView* view, EngineModel* model);

	virtual void gameLoop();
	void closeWindow() const;
	virtual ~EngineController();
};
