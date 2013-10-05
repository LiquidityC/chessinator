#include <unistd.h>

#include "countdowntimertest.h"
#include "../src/countdowntimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CountdownTimerTest );

void CountdownTimerTest::test_timer()
{
	cengine::CountdownTimer timer;
	timer.set_time(3);

	timer.start();

	sleep(1);
	
	CPPUNIT_ASSERT ( timer.time_remaining() < 3 );
	CPPUNIT_ASSERT ( timer.time_remaining() > 0 );
}
