#pragma once

#include <iostream>
// #include <chrono>
#include "Renderer.h"

class Timer
{
protected:
	long iterationCount;		// Counts amount of iterations of the game model.
	GLint64 startTimestamp;		// Start time in ns.
	long long lastTickTimestamp;// Timestamp of last tick.
	GLint64	timelimit;			// Save a converted time limit.
public:
	// for converting a given time period in seconds to nanoseconds
	const GLint64 SECONDS_TO_NANO = 1000000000;

	Timer();
	Timer(int timelimit);
	~Timer();

	// Returns the time passed since creation of the window,
	// counted in ticks dependant on latency.
	// Used for setting Game Session Clocks that adapt themselves to slowdown during gameplay.
	//@returns Time passed in ns.
	int getTimePassed() const;
	int getIterationCount() const;

	// For checking whether enough time has passed since the last iteration,
	// and thus the next iteration should be started
	bool hasTickTimePassed(); 
};