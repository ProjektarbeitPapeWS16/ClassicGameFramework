#pragma once
#include "Config.h"
#include "Level.h"
#include <chrono>	// for exact time measurment independant from CPU usage
#include <thread>

typedef std::chrono::high_resolution_clock Clock;

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
