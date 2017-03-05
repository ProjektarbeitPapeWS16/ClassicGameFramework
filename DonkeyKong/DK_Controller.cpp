#include "DK_Controller.h"

#include <glfw3.h>
#include "Display.h"
//#include "Drawable.h"
#include "Session.h"
#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
//#include "Level.h"

//#include "Entity_Jumpman.h"
//#include "DK_Level.h"
#include "DK_Model.h"

DK_Controller::DK_Controller(DK_View* view, DK_Model* model)
		: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
	{
		// Assign key listeners to model functions

		this->model->getKeyPressedListeners()->insert_or_assign(GLFW_KEY_ESCAPE, new std::function<void()>(DK_Model::keyEscPress));		// Esc

		this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_UP, new std::function<void()>(DK_Model::keyUpPress));				// Up Arrow
		this->model->getKeyDownKeys()->push_back(GLFW_KEY_UP);

		this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_DOWN, new std::function<void()>(DK_Model::keyDownPress));			// Down Arrow
		this->model->getKeyDownKeys()->push_back(GLFW_KEY_DOWN);

		this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_LEFT, new std::function<void()>(DK_Model::keyLeftPress));			// Left Arrow
		this->model->getKeyDownKeys()->push_back(GLFW_KEY_LEFT);

		this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_RIGHT, new std::function<void()>(DK_Model::keyRightPress));		// Right Arrow
		this->model->getKeyDownKeys()->push_back(GLFW_KEY_RIGHT);

		this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_SPACE, new std::function<void()>(DK_Model::keySpacePress));		// Spacebar
		this->model->getKeyDownKeys()->push_back(GLFW_KEY_SPACE);
	}

DK_Controller::~DK_Controller()
{
}

void DK_Controller::cycle()
{
}

void DK_Controller::handleRequest(Input input)
{
}

