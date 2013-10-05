#ifndef _TIMER_H
#define _TIMER_H

#include <ctime>

namespace cengine
{
	class Timer
	{
		private:
			time_t started_time, paused_time;
			bool started, paused;

		public:

			Timer() : started(false), paused(false) { };

			unsigned int get_time() const;

			bool is_started() const;

			bool is_paused() const;

			void stop();

			void start();

			void pause();

			void unpause();
	};
}

#endif
