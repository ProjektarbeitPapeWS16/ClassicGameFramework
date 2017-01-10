#include "SpacePanicController.h"

#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
#include <glfw3.h>
#include "Display.h"
#include "Drawable.h"

// TODO make static and put in Model
void upDown()
{
	Drawable* drawable = EngineView::getInstance()->display->getDrawables()->at(0);
	drawable->setPosY(drawable->getPosY() + 5);
}


void downDown()
{
	Drawable* drawable = EngineView::getInstance()->display->getDrawables()->at(0);
	drawable->setPosY(drawable->getPosY() - 5);
}

void leftDown()
{
	Drawable* drawable = EngineView::getInstance()->display->getDrawables()->at(0);
	drawable->setPosX(drawable->getPosX() - 5);
}

void rightDown()
{
	Drawable* drawable = EngineView::getInstance()->display->getDrawables()->at(0);
	drawable->setPosX(drawable->getPosX() + 5);
}

void escPress()
{
	EngineController::getInstance()->closeWindow();
}


SpacePanicController::SpacePanicController(SpacePanicView* view, SpacePanicModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
{
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_ESCAPE, new std::function<void()>(escPress));// , model));

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(upDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_UP);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(downDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_DOWN);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(leftDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_LEFT);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(rightDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_RIGHT);
}

SpacePanicController::~SpacePanicController()
{
}
