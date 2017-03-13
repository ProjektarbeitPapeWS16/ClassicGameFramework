#pragma once
#include "Config.h"


class Level;
class Session
{
protected:
	int lifes;
	unsigned __int64 creationTime = Config::currentTimeMillis();
	int score;
	Level* level;	//[C] bei Init: Startbildschirm?
	int defaultLifes;
public:
	// Konstruktor
	Session();
	Session(int defaultLifes, int defaultScore);
	Session(int defaultLifes, int defaultScore, Level* level);
	int getLifes() const;
	void setLifes(int lifes);

	unsigned __int64 getCreationTime() const;
	unsigned __int64 getPassedTime() const;

	int getScore() const;
	void setScore(int score);

	Level* getLevel() const;
	void setLevel(Level* level);
};
