#ifndef MICROCPP_TIMER_H
#define MICROCPP_TIMER_H

enum TimerStates {
	timerStatePause,			// Timer is currently not running
	timerStateRunning			// Timer is currently running
};

class Timer
{
	TimerStates state;
	u32 initialTicks;		// Number of ticks when starting the timer
	u32 ticksOnPause;		// Number of ticks when pausing the timer

public:
	Timer(float initialTime=0);
	~Timer();

	float getTime();
	void start();
	void stop();
	void reset(float initialTime=0);
};

#endif
