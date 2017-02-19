#include "PacManController.h"

#include "PacManView.h"
#include "PacManModel.h"
#include <glfw3.h>
#include "Display.h"
#include "Drawable.h"
#include "PlayerEntity.h"
#include "Session.h"
#include "Level.h"



PacManController::PacManController(PacManView* view, PacManModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
{
	this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_ESCAPE, new std::function<void()>(PacManModel::keyEscPress));// , model));

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(PacManModel::keyUpPress));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_UP);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(PacManModel::keyDownPress));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_DOWN);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(PacManModel::keyLeftPress));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_LEFT);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(PacManModel::keyRightPress));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_RIGHT);
}

PacManController::~PacManController()
{
}

void PacManController::cycle()
{

}
