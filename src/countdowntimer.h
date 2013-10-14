#ifndef _COUNTDOWN_TIMER_H
#define _COUNTDOWN_TIMER_H

#include "timer.h"

namespace cengine
{
	class CountdownTimer : public Timer
	{
		private:
			unsigned int countdown_time;

		public:

			CountdownTimer() : Timer(), countdown_time(300) {  };

			CountdownTimer(time_t (*f)(time_t*)) : Timer(f), countdown_time(300) {  };

			void set_time(unsigned int);

			unsigned int time_remaining() const;

			void reset();
	};
}


#endif
