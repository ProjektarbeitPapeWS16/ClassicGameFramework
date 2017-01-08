#pragma once

typedef int Key;
typedef char byte;


#include <chrono>

/// <summary>
/// Gets the current time in milliseconds
/// </summary>
/// <returns>current time in milliseconds</returns>
static long currentTimeMillis()
{
	// http://stackoverflow.com/questions/2831841/how-to-get-time-in-millis-in-c-just-like-java
	auto time = std::chrono::system_clock::now(); // get the current time

	auto since_epoch = time.time_since_epoch(); // get the duration since epoch

	// I don't know what system_clock returns
	// I think it's uint64_t nanoseconds since epoch
	// Either way this duration_cast will do the right thing
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

	return millis.count(); // just like java (new Date()).getTime();
}

struct Position
{
	int x;
	int y;
};

struct Boundaries
{
	Position position;
	int width;
	int height;
	
	Boundaries(int x, int y, int width, int height)
	{
		this->position.x = x;
		this->position.y = y;
		this->width = width;
		this->height = height;
	}
};
