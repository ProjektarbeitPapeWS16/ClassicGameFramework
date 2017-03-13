#include "Session.h"

#include "Config.h"
#include "Level.h"

Session::Session() : Session(3, 0, nullptr)
{
}

Session::Session(int defaultLifes, int defaultScore) : Session(defaultLifes, defaultScore, nullptr)
{
}

Session::Session(int defaultLifes, int defaultScore, Level* level) : lifes(defaultLifes), score(defaultScore), level(level), defaultLifes(defaultLifes)
{
}

int Session::getLifes() const
{
	return lifes;
}

void Session::setLifes(int lifes)
{
	this->lifes = lifes;
}

unsigned __int64 Session::getCreationTime() const
{
	return creationTime;
}

unsigned __int64 Session::getPassedTime() const
{
	return Config::currentTimeMillis() - creationTime;
}

int Session::getScore() const
{
	return score;
}

void Session::setScore(int score)
{
	this->score = score;
}

Level* Session::getLevel() const
{
	return level;
}

void Session::setLevel(Level* level)
{
	if (this->level != nullptr)
	{
		delete this->level;
	}

	this->level = level;
}
