#include "PacManController.h"
#include "PacManView.h"
#include "PacManModel.h"
#include <glfw3.h>

void upPress()
{
}

void upRelease()
{
}

void downPress()
{
}

void downRelease()
{
}

void leftPress()
{
}

void leftRelease()
{
}

void rightPress()
{
}

void rightRelease()
{
}

void escPress()
{
	EngineModel::gameloopShouldEnd = true;
}

PacManController::PacManController(PacManView* view, PacManModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
{
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_ESCAPE, new std::function<void()>(escPress));

	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(upPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(downPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(leftPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(rightPress));

	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(upRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(downRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(leftRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(rightRelease));
}

void PacManController::gameLoop()
{
	while (!EngineModel::gameloopShouldEnd)
	{
		this->view->update();
		//this->model->nextIteration();
	}
}

PacManController::~PacManController()
{
}
