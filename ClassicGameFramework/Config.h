#pragma once

typedef int Key;
typedef char byte;


#include <chrono>
namespace sc = std::chrono;

/// <summary>
/// Gets the current time in milliseconds
/// </summary>
/// <returns>current time in milliseconds</returns>
static long currentTimeMillis()
{
	// http://stackoverflow.com/questions/2831841/how-to-get-time-in-millis-in-c-just-like-java
	auto time = sc::system_clock::now(); // get the current time

	auto since_epoch = time.time_since_epoch(); // get the duration since epoch

												// I don't know what system_clock returns
												// I think it's uint64_t nanoseconds since epoch
												// Either way this duration_cast will do the right thing
	auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);

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
};