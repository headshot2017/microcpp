#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <nds.h>
#include <time.h>

#include <microcpp/timer.h>
#include <microcpp/vars.h>

// This is the speed of our timer (about 32728.5 Hz)
#define TIMER_CLOCK (BUS_CLOCK/1024)
// We will be using timer 0
// Timer 3 may be used by dswifi
#define TIMER_ID 0

// Counting the ticks produced by the hardware timer TIMER_ID
u32 ticks = 0;


Timer::Timer(float initialTime)
{
	// Reset the timer with an initial time (in ms)
	state = timerStatePause;
	initialTicks = 0;
	ticksOnPause = initialTime * TIMER_CLOCK / 1000;
}

Timer::~Timer()
{
	stop();
}

float Timer::getTime()
{
	float timerTicks = 0;
	
	ticks += timerElapsed(TIMER_ID);
	
	if (state == timerStateRunning)
		timerTicks = ticks - initialTicks;
	else if (state == timerStatePause)
		timerTicks = ticksOnPause - initialTicks;
	
	return timerTicks / TIMER_CLOCK * 1000;
}

void Timer::start()
{
	ticks += timerElapsed(TIMER_ID);
	
	if (state == timerStatePause)
	{
		state = timerStateRunning;
		initialTicks = ticks - ticksOnPause + initialTicks;
		ticksOnPause = 0;
	}
}

void Timer::stop()
{
	ticks += timerElapsed(TIMER_ID);
	
	if (state == timerStateRunning)
	{
		state = timerStatePause;
		ticksOnPause = ticks;
	}
}

void Timer::reset(float initialTime)
{
	// Reset the timer with an initial time (in ms)
	state = timerStatePause;
	initialTicks = 0;
	ticksOnPause = initialTime * TIMER_CLOCK / 1000;
}
