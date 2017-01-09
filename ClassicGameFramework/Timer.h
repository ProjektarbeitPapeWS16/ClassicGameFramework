#pragma once

#include <iostream>
// #include <chrono>
#include "Renderer.h"

class Timer
{
	//int startTime;
	GLint64 timestamp; // Start time in ns.
	GLint64	timelimit; // Save a converted time limit.
public:
	// for converting a given time period in seconds to nanoseconds
	const GLint64 SECONDS_TO_NANO = 1000000000;

	/// <summary> Initializes the timer. </summary>
	void init(int timelimit);
	// TODO: Take latency into consideration by using OpenGL methods.
	/// <summary>
	/// Returns the time passed since creation of the window,
	/// counted in ticks dependant on latency.
	/// Used for setting Game Session Clocks that adapt themselves to slowdown during gameplay.
	/// </summary>
	/// <returns>Time passed in ns.</returns>
	int getTimePassed() const;
};