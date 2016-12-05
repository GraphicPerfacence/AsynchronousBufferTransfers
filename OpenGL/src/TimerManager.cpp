//
//  TimerManager.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/sys.h"

#if defined X_OS_MAC || defined X_OS_MAC9
#include <unistd.h>
#include <chrono>
#elif defined X_OS_WIN32 || defined X_OS_WIN64
#include <windows.h>
#endif

#include "../include/TimerManager.h"


// This calculates our current scene's frames per second and displays it in the console
double TimeManager::CalculateFrameRate(bool writeToConsole = false)
{
	// Below we create a bunch of static variables to track the deltas of the time.

	static double framesPerSecond = 0.0f;								// This will store our fps
	static double startTime = GetTime();								// This will hold the time per second to test against
	static double lastTime = GetTime();									// This will hold the time from the last frame
	static char   strFrameRate[50] = { 0 };								// We will store the string here for the window title
	static double currentFPS = 0.0f;									// This stores the current frames per second

	// Grab the current time in seconds from our environment's time function wrapped in our WindowManager
	CurrentTime = GetTime();

	// Calculate our delta time, which is the time that has elapsed since the last time we checked the time
	DeltaTime = CurrentTime - lastTime;

	// Now store the lastTime as the currentTime to then get the time passed since the last frame
	lastTime = CurrentTime;

	// Increase the frame counter
	++framesPerSecond;

	// if a second has passed we can get the current frame rate
	if (CurrentTime - startTime > 1.0f)
	{
		// Here we set the startTime to the currentTime.  This will be used as the starting point for the next second.
		// This is because GetTime() counts up, so we need to create a delta that subtract the current time from.
		startTime = CurrentTime;

		// Show the frames per second in the console window if desired
		if (writeToConsole)
			fprintf(stderr, "Current Frames Per Second: %d\n", int(framesPerSecond));

		// Store the current FPS since we reset it down below and need to store it to return it
		currentFPS = framesPerSecond;

		// Reset the frames per second
		framesPerSecond = 0;
	}

	// Return the most recent FPS
	return currentFPS;
}


// This returns the current time in seconds (uses C++ 11 system_clock)
double TimeManager::GetTime()
{
#if defined X_OS_MAC || defined X_OS_MAC9
	// Grab the current system time since 1/1/1970, otherwise know as the Unix Timestamp or Epoch
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();

	// Convert the system time to milliseconds
	auto ms = std::chrono::duration_cast<milliseconds>(beginningOfTime).count();

	// Return the time in seconds and give us a fractional value (important!)
	return ms * 0.001;

#elif defined X_OS_WIN32 || defined X_OS_WIN64
    SYSTEMTIME sysUnixEpoch;
    sysUnixEpoch.wYear = 1970;
    sysUnixEpoch.wMonth = 1;
    sysUnixEpoch.wDayOfWeek = 4;
    sysUnixEpoch.wDay = 1;
    sysUnixEpoch.wHour = 0;
    sysUnixEpoch.wMinute = 0;
    sysUnixEpoch.wSecond = 0;
    sysUnixEpoch.wMilliseconds = 0;

    FILETIME unixEpoch;
    SystemTimeToFileTime(&sysUnixEpoch, &unixEpoch);

    ULARGE_INTEGER unixEpochValue;
    unixEpochValue.HighPart = unixEpoch.dwHighDateTime;
    unixEpochValue.LowPart = unixEpoch.dwLowDateTime;

    FILETIME systemTime;
    GetSystemTimeAsFileTime(&systemTime);

    ULARGE_INTEGER systemTimeValue;
    systemTimeValue.HighPart = systemTime.dwHighDateTime;
    systemTimeValue.LowPart = systemTime.dwLowDateTime;

    long long diffHundredNanos = systemTimeValue.QuadPart - unixEpochValue.QuadPart;
    return diffHundredNanos / 10000;
#endif
    return 0.0;
}


// This pauses the current thread for an amount of time in milliseconds
void TimeManager::Sleep(int ms)
{
	// Use the C++ 11 sleep_for() function to pause the current thread

#if defined  X_OS_MAC || defined X_OS_MAC9
	sleep(ms);
#elif defined X_OS_WIN32 || defined X_OS_WIN64
	Sleep(ms);
#endif //  X_OS_MAC || define X_OS_MAC9
}

TimeManager::TimeManager()
{
	DeltaTime = 0.0;
	CurrentTime = 0.0;
}
