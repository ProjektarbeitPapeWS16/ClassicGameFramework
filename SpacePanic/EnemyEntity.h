﻿#pragma once
#include "Entity.h"

class GameConfig;

class EnemyEntity : public Entity
{
public:
	typedef enum
	{
		LAUF_1,
		LAUF_2
	} EnemyState;
private:
	EnemyState state;
	unsigned long counter = 0;
public:
	EnemyEntity(GameConfig* config, Position* position);
	void execute();
	Image* lauf1;
	Image* lauf2;

	

	Image* getImage() override;
};
