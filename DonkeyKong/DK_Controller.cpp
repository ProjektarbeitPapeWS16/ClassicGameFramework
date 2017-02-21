//#include "stdafx.h"DK_Controller
#include "DK_Controller.h"

#include "DK_Controller.h"

#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
#include <glfw3.h>
#include "Display.h"
#include "Drawable.h"
#include "Entity_Jumpman.h"
#include "Level_25m.h"
#include "Session.h"

// TODO make static and put in Model
void upDown()
{
	Entity_Jumpman* player = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(Entity_Jumpman::MOVE_UP);
}


void downDown()
{
	Entity_Jumpman* player = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(Entity_Jumpman::MOVE_DOWN);
}

void leftDown()
{
	Entity_Jumpman* player = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(Entity_Jumpman::MOVE_LEFT);
}

void rightDown()
{
	Entity_Jumpman* player = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(Entity_Jumpman::MOVE_RIGHT);
}

void escPress()
{
	EngineController::getInstance()->closeWindow();
}


DK_Controller::DK_Controller(DK_View* view, DK_Model* model)
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

DK_Controller::~DK_Controller()
{
}

long cycles = 0L;
void DK_Controller::cycle()
{
	if (cycles % 4 == 0)
	{
		Entity_Jumpman* player = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
		if (player != nullptr)
		{
			player->execute();
		}

		std::vector<EnemyEntity*>* enemys = static_cast<Level_25m*>(EngineModel::getInstance()->getSession()->getLevel())->getEnemys();
		for (int i = 0; i < enemys->size(); i++)
		{
			enemys->at(i)->execute();
		}

	}
	cycles++;
}

