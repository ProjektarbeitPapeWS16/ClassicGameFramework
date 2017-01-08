#include "SpacePanicController.h"

#include "EngineModel.h"
#include "EngineView.h"
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
	//((EngineController*)(model))->closeWindow();
}


SpacePanicController::SpacePanicController(SpacePanicView* view, SpacePanicModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
{
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_ESCAPE, new std::function<void()>(escPress));// , model));

	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(upPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(downPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(leftPress));
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(rightPress));

	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(upRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(downRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(leftRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(rightRelease));
}

SpacePanicController::~SpacePanicController()
{
}
