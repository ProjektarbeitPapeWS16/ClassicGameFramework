#include "EngineController.h"
#include "../SpacePanic/SpacePanicModel.h"

void EngineController::key_callback(GLFWwindow * window, Key key, int scancode, int action, int mode)
{
	if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	{
		EngineModel::gameloopShouldEnd = true;
	}
	/*
	if (action == GLFW_PRESS && keyPressedListeners.find(key) != keyPressedListeners.end())
	{
		keyPressedListeners.at(key)();
	}
	else if (action == GLFW_RELEASE && keyReleasedListeners.find(key) != keyReleasedListeners.end())
	{
		keyReleasedListeners.at(key)();
	}*/
}

EngineController::EngineController( EngineView& view,  EngineModel& model): view(view), model(model)
{
	glfwSetKeyCallback(view.renderer.window, key_callback);
}

void EngineController::gameLoop()
{
	
}

EngineController::~EngineController()
{
}
