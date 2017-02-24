#include "Session.h"

#include "Config.h"
#include "Level.h"

Session::Session() : Session(3, 0)
{

}

Session::Session(int defaultLifes, int defaultScore) : lifes(defaultLifes), score(defaultScore), level(nullptr)
{

}

int Session::getLives()
{
	return lifes;
}

void Session::setLifes(int lifes)
{
	this->lifes = lifes;
}

unsigned __int64 Session::getCreationTime()
{
	return creationTime;
}

unsigned __int64 Session::getPassedTime()
{
	return Config::currentTimeMillis() - creationTime;
}

int Session::getScore()
{
	return score;
}

void Session::setScore(int score)
{
	this->score = score;
}

Level * Session::getLevel()
{
	return level;
}

void Session::setLevel(Level * level)
{
	if(this->level != nullptr)
	{
		delete this->level;
	}

	this->level = level;
}
