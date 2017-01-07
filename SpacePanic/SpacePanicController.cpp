﻿#include "SpacePanicController.h"

//set<Key> SpacePanicController::keys = set<Key>();

SpacePanicController::SpacePanicController(const SpacePanicView& view, const SpacePanicModel& model): EngineController((EngineView&)view, (EngineModel&)model)
{
	/*
	//this->view.addKeyPressedListener(GLFW_KEY_ESCAPE, []() { gameloopShouldEnd = true; });

	this->model.addKeyPressedListener(GLFW_KEY_ESCAPE, []() { SpacePanicController::keys.insert(GLFW_KEY_ESCAPE); });
	this->model.addKeyReleasedListener(GLFW_KEY_ESCAPE, []() { SpacePanicController::keys.erase(GLFW_KEY_ESCAPE); });

	this->model.addKeyPressedListener(GLFW_KEY_UP, []() { SpacePanicController::keys.insert(GLFW_KEY_UP); });
	this->model.addKeyReleasedListener(GLFW_KEY_UP, []() { SpacePanicController::keys.erase(GLFW_KEY_UP); });

	this->model.addKeyPressedListener(GLFW_KEY_DOWN, []() { SpacePanicController::keys.insert(GLFW_KEY_DOWN); });
	this->model.addKeyReleasedListener(GLFW_KEY_DOWN, []() { SpacePanicController::keys.erase(GLFW_KEY_DOWN); });

	this->model.addKeyPressedListener(GLFW_KEY_LEFT, []() { SpacePanicController::keys.insert(GLFW_KEY_LEFT); });
	this->model.addKeyReleasedListener(GLFW_KEY_LEFT, []() { SpacePanicController::keys.erase(GLFW_KEY_LEFT); });

	this->model.addKeyPressedListener(GLFW_KEY_RIGHT, []() { SpacePanicController::keys.insert(GLFW_KEY_RIGHT); });
	this->model.addKeyReleasedListener(GLFW_KEY_RIGHT, []() { SpacePanicController::keys.erase(GLFW_KEY_RIGHT); });

	this->model.addKeyPressedListener(GLFW_KEY_SPACE, []() { SpacePanicController::keys.insert(GLFW_KEY_SPACE); });
	this->model.addKeyReleasedListener(GLFW_KEY_SPACE, []() { SpacePanicController::keys.erase(GLFW_KEY_SPACE); });

	this->model.addKeyPressedListener(GLFW_KEY_LEFT_SHIFT, []() { SpacePanicController::keys.insert(GLFW_KEY_LEFT_SHIFT); });
	this->model.addKeyReleasedListener(GLFW_KEY_LEFT_SHIFT, []() { SpacePanicController::keys.erase(GLFW_KEY_LEFT_SHIFT); });
	*/
}

void SpacePanicController::gameLoop()
{
	while(!EngineModel::gameloopShouldEnd)
	{
		this->view.update();
		//this->model.nextIteration(keys);
	}
}

SpacePanicController::~SpacePanicController()
{
}
