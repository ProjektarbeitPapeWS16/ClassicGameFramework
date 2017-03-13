#pragma once
#include"Renderer.h"
#include "Timer.h"

// Base Constructor; for Timer with (virtually) no time limit.
Timer::Timer() : Timer(LLONG_MAX)
{
}

// Constructor for time limit
Timer::Timer(int timelimit)
{
	// set GPU timestamp when all previously given commands have been issued
	iterationCount = 0;
	//glGetInteger64v(GL_TIMESTAMP, &startTimestamp);
	startTimestamp = 0;
	this->lastTickTimestamp = startTimestamp;
	this->timelimit = timelimit; //* this->SECONDS_TO_NANO;
	// alternative: https://www.opengl.org/sdk/docs/man4/html/glQueryCounter.xhtml
}

Timer::~Timer() {}

// Returns time passed in seconds since session start
// @return time passed in seconds since session start
int Timer::getTimePassed() const
{
	auto timeInNS = (GL_TIMESTAMP - startTimestamp);
	auto timeInS = (std::nearbyint(timeInNS / SECONDS_TO_NANO));
	return static_cast<int>(timeInS);
}

// Getter for current count of iterations.
int Timer::getIterationCount() const
{
	return iterationCount;
}

// Checks if enough time has passed to allow next iteration.
// Affects: @lastTickTimestamp -- If true; gets set to current time.
//          @iterationCount -- If true; gets incremented.
bool Timer::hasTickTimePassed() 
{
	long long currTime = GL_TIMESTAMP;
	if(currTime - lastTickTimestamp > 1000)
	{
		lastTickTimestamp = currTime;
		iterationCount++;
		return true;
	}
	return false;
}

