#include "DonkeyKongController.h"

#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
#include <glfw3.h>
#include "Display.h"
#include "Drawable.h"
#include "PlayerEntity.h"
#include "Stage1.h"
#include "Session.h"

// TODO make static and put in Model
void upDown()
{
	PlayerEntity* player = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_UP);
}


void downDown()
{
	PlayerEntity* player = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_DOWN);
}

void leftDown()
{
	PlayerEntity* player = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_LEFT);
}

void rightDown()
{
	PlayerEntity* player = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_RIGHT);
}

void escPress()
{
	EngineController::getInstance()->closeWindow();
}


DonkeyKongController::DonkeyKongController(DonkeyKongView* view, DonkeyKongModel* model)
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

DonkeyKongController::~DonkeyKongController()
{
}

long cycles = 0L;
void DonkeyKongController::cycle()
{
	if(cycles % 4 == 0)
	{
		PlayerEntity* player = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
		if(player != nullptr)
		{
			player->execute();
		}

		std::vector<EnemyEntity*>* enemys = static_cast<Stage1*>(EngineModel::getInstance()->getSession()->getLevel())->getEnemys();
		for(int i = 0; i < enemys->size(); i++)
		{
			enemys->at(i)->execute();
		}
		
	}
	cycles++;
}
