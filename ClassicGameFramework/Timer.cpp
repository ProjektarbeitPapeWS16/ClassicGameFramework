#pragma once
#include"Renderer.h"
#include "Timer.h"

void Timer::init(int timelimit)
{
	// set GPU timestamp when all previously given commands have issued
	glGetInteger64v(GL_TIMESTAMP, &timestamp);
	this->timelimit = timelimit * this->SECONDS_TO_NANO;
	// printf("Milliseconds: %f\n", timer / 1000000.0);
	// alternative: https://www.opengl.org/sdk/docs/man4/html/glQueryCounter.xhtml
	// glQueryCounter(GL_TIMESTAMP; &timestamp);
}

/// <summary>
/// returns time passed in seconds since session start
/// </summary>
/// <returns>time passed in seconds since session start</returns>
int Timer::getTimePassed() const
{
	auto timeInNS = (GL_TIMESTAMP - timestamp);
	auto timeInS = (std::nearbyint(timeInNS / SECONDS_TO_NANO));
	return static_cast<int>(timeInS);
}
