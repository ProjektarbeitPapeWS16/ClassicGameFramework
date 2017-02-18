#pragma once

#include <chrono>

struct Config
{
	/// <summary>
	/// Gets the current time in milliseconds
	/// </summary>
	/// <returns>current time in milliseconds</returns>
	static __int64 currentTimeMillis();
};
