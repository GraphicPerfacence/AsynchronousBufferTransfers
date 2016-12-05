//
//  TimerManager.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__TimerManager__
#define __OpenGL__TimerManager__

#include <stdio.h>
class TimeManager
{
public:

	// The function to get the instance of the manager, or initialize and return the instance.
	// By creating a static variable of the instance we ensure this only gets created once.
	// This is also thread-safe in C++ 11 according to the specifications.
	static TimeManager& Instance()
	{
		static TimeManager instance;

		return instance;
	}

	// This calculates our current scene's frames per second and displays it in the console
	double CalculateFrameRate(bool writeToConsole);

	// This returns the current time in seconds (since 1/1/1970, call "epoch")
	double GetTime();

	// This pauses the current thread for an amount of time in milliseconds
	void Sleep(int milliseconds);

	// This is the time slice that stores the total time in seconds that has elapsed since the last frame
	double DeltaTime;

	// This is the current time in seconds
	double CurrentTime;

private:
	TimeManager();								// Private so that it can  not be called
	TimeManager(TimeManager const&);				// copy constructor is private
	TimeManager& operator=(TimeManager const&);		// assignment operator is private
};
#endif /* defined(__OpenGL__TimerManager__) */
