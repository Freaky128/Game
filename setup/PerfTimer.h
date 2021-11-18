#pragma once

#include "GameC.h"

class PerfTimer
{
public:
	//Initializes variables
	PerfTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint64 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint64 startTicks;

	//The ticks stored when the timer was paused
	Uint64 pausedTicks;

	//The timer status
	bool paused;
	bool started;
};