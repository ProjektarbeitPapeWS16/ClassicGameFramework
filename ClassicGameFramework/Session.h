#pragma once
#include "Config.h"
#include "Level.h"


class Session
{
	int lifes;
	unsigned long creationTime = currentTimeMillis();
	int score;


public:


	int getLifes();
	void setLifes(int lifes);

	unsigned long getCreationTime();
	unsigned long getPassedTime();

	int getScore();
	void setScore(int score);

	Level* getLevel();
	void setLevel(Level* level);
	
};
