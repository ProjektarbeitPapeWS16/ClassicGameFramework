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
	GLuint m_iTimeQuery;
	GLuint timeElapsed = 0;
}

int Timer::getTimePassed()
{
	return 0;
}
