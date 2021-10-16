#include "PerfTimer.h"

PerfTimer::PerfTimer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void PerfTimer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetPerformanceCounter();
    pausedTicks = 0;
}

void PerfTimer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;

    //Clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void PerfTimer::pause()
{
    //If the timer is running and isn't already paused
    if (started && !paused)
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetPerformanceCounter() - startTicks;
        startTicks = 0;
    }
}

void PerfTimer::unpause()
{
    //If the timer is running and paused
    if (started && paused)
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetPerformanceCounter() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

Uint32 PerfTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (started)
    {
        //If the timer is paused
        if (paused)
        {
            //Return the number of ticks when the timer was paused
            time = pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetPerformanceCounter() - startTicks;
        }
    }

    return time;
}

bool PerfTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return started;
}

bool PerfTimer::isPaused()
{
    //Timer is running and paused
    return paused && started;
}