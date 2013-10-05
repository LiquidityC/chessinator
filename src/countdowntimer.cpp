#include "countdowntimer.h"
#include "timer.h"

namespace cengine
{
	unsigned int CountdownTimer::time_remaining() const
	{
		if (get_time() > countdown_time) {
			return 0;
		}

		return countdown_time - get_time();
	}

	void CountdownTimer::set_time(unsigned int time)
	{
		reset();
		countdown_time = time;
	}

	void CountdownTimer::reset()
	{
		stop();
	}
}
