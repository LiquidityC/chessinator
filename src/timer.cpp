#include <ctime>

#include "timer.h"

namespace cengine
{
	Timer::Timer() : started(false), paused(false)
	{
		timeFunction = time;
	}

	Timer::Timer(time_t (*f)(time_t*)) : started(false), paused(false)
	{
		timeFunction = f;
	}

	unsigned int Timer::get_time() const
	{
		if (started) {
			time_t current_time;

			if (paused) {
				return paused_time;
			} else {
				timeFunction(&current_time);
				return current_time - started_time;
			}
		}
		return 0;
	}

	bool Timer::is_started() const
	{
		return started;
	}

	bool Timer::is_paused() const
	{
		return paused;
	}

	void Timer::stop()
	{
		started = false;
		paused = false;
	}

	void Timer::start()
	{
		started = true;
		timeFunction(&started_time);
	}

	void Timer::pause()
	{
		paused = true;
		timeFunction(&paused_time);
		paused_time -= started_time;
	}
	
	void Timer::unpause()
	{
		paused = false;
		paused_time = 0;
	}
}
