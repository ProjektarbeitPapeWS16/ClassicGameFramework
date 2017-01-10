#include "EngineController.h"
#include "EngineView.h"
#include "Renderer.h"
#include "EngineModel.h"

EngineController* EngineController::instance = nullptr;
EngineModel* EngineController::staticModel = nullptr;

EngineController* EngineController::getInstance()
{
	return instance;
}

void EngineController::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode)
{
	if (EngineController::staticModel != nullptr)
	{
		EngineController::staticModel->key_callback(window, key, scancode, action, mode);
	}

	//if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	//{
	//	EngineModel::escPressed = true;
	//}
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

EngineController::EngineController(EngineView* view, EngineModel* model): view(view), model(model)
{
	instance = this;
	EngineController::staticModel = model;
	//TODO: window ist NULL bei erstem Aufruf?
	glfwSetKeyCallback(view->renderer->window, key_callback);
}

void EngineController::gameLoop()
{
	EngineController::lastTime = glfwGetTime();
	while (glfwWindowShouldClose(view->renderer->window) == 0)
	{
		double now = glfwGetTime();
		EngineController::timeElapsed = now - EngineController::lastTime;
		EngineController::lastTime = now;

		model->key_down();
		model->nextIteration(); 
		cycle();
		view->update();
		glfwPollEvents();
	}
}

void EngineController::closeWindow() const
{
	glfwSetWindowShouldClose(view->renderer->window, 1);
}

EngineController::~EngineController()
{
}
