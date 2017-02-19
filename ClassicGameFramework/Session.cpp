#include "Session.h"

#include "Config.h"

Session::Session()
{

}

int Session::getLifes()
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
	this->level = level;
}
