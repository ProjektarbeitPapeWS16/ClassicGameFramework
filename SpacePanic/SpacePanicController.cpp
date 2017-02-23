#include "SpacePanicController.h"

#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
#include <glfw3.h>
#include "Display.h"
#include "PlayerEntity.h"
#include "Stage.h"
#include "Session.h"
#include "EnemyEntity.h"
#include "SpacePanicModel.h"
#include "SpacePanicSession.h"

// TODO make static and put in Model
void upDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_UP);
}


void downDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_DOWN);
}

void leftDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_LEFT);
}

void rightDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::MOVE_RIGHT);
}

void ctrlDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::DIG);
}

void altDown()
{
	auto player = static_cast<Stage*>(EngineModel::getInstance()->getSession()->getLevel())->getPlayer();
	player->request(PlayerEntity::UNDIG);
}

void escPress()
{
	EngineModel::getInstance()->shouldClose = true;
}


SpacePanicController::SpacePanicController(SpacePanicView* view, SpacePanicModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model)), model(model)
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

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_LEFT_CONTROL, new std::function<void()>(ctrlDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_LEFT_CONTROL);

	this->model->getKeyDownListeners()->insert_or_assign(GLFW_KEY_LEFT_ALT, new std::function<void()>(altDown));
	this->model->getKeyDownKeys()->push_back(GLFW_KEY_LEFT_ALT);
}

SpacePanicController::~SpacePanicController()
{
}

long cycles = 0L;
void SpacePanicController::cycle()
{

	if(cycles++ % 4 == 0)
	{
		SpacePanicSession* session = static_cast<SpacePanicSession*>(model->getSession());

		session->respawnIfPossible();

		auto player = session->getStage()->getPlayer();
		if(player != nullptr)
		{
			player->execute();
		}

		auto enemys = session->getStage()->getEnemys();
		for(auto i = 0; i < enemys->size(); i++)
		{
			enemys->at(i)->execute();
		}
		
		 delete session->getStage()->getCollisions();
	}
}
