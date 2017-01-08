﻿#pragma once

static long currentTimeMillis();
class Level;


class Session
{
	int lifes;
	unsigned long creationTime = currentTimeMillis();
	int score;
	Level* level;	//[C] bei Init: Startbildschirm?

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
